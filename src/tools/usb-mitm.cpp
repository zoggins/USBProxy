/*This file is part of USBProxy.
 */

#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <memory.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/poll.h>
#include <sys/utsname.h>

#include <iostream>

#include "TRACE.h"
#include "Manager.h"
#include "ConfigParser.h"
#include "version.h"

static unsigned debug=0;

Manager* manager;

void usage(char *arg) {
	printf("usb-mitm - command line tool for controlling USBProxy\n");
	printf("Usage: %s [OPTIONS]\n", arg);
	printf("Options:\n");
	printf("\t-v <vendorId> VendorID of target device\n");
	printf("\t-p <productId> ProductID of target device\n");
	printf("\t-P <PluginName> Use PluginName (order is preserved)\n");
	printf("\t-D <DeviceProxy> Use DeviceProxy\n");
	printf("\t-H <HostProxy> Use HostProxy\n");
	printf("\t-d Enable debug messages (-dd for increased verbosity)\n");
	printf("\t-s Server mode, listen on port 10400\n");
	printf("\t-c <hostname | address> Client mode, connect to server at hostname or address\n");
	printf("\t-l Enable stream logger (logs to stderr)\n");
	printf("\t-i Enable UDP injector\n");
	printf("\t-x RetroSpy Xbox mode\n");
	printf("\t-y RetroSpy PlayStation Classic mode\n");
	printf("\t-z RetroSpy Switch mode\n");
	printf("\t-u RetroSpy PS3 mode\n");
	printf("\t-b RetroSpy Xbox 360 mode\n");
	printf("\t-g RetroSpy NeoGeo mode\n");
	printf("\t-m RetroSpy TG16 mode\n");
	printf("\t-V RetroSpy VCS mode\n");
	printf("\t-n RetroSpy Evercade mode\n");
	printf("\t-q RetroSpy PS4 mode\n");
	printf("\t-5 RetroSpy A500 Mini mode\n");
	printf("\t-6 RetroSpy Genesis Mini mode\n");
	printf("\t-k Keylogger with ROT13 filter (for demo), specify optional filename to output to instead of stderr\n");
	printf("\t-w <filename> Write to pcap file for viewing in Wireshark\n");
	printf("\t-h Display this message\n");
}

void cleanup(void) {
}

/*
 * sigterm: stop forwarding threads, and/or hotplug loop and exit
 * sighup: reset forwarding threads, reset device and gadget
 */
void handle_signal(int signum)
{
	struct sigaction action;
	switch (signum) {
		case SIGTERM:
		case SIGINT:
			if(signum == SIGTERM)
				fprintf(stderr, "Received SIGTERM, stopping relaying...\n");
			else
				fprintf(stderr, "Received SIGINT, stopping relaying...\n");
			if (manager) {manager->stop_relaying();}
			fprintf(stderr, "Exiting\n");
			memset(&action, 0, sizeof(struct sigaction));
			action.sa_handler = SIG_DFL;
			sigaction(SIGTERM, &action, NULL);
			break;
		case SIGHUP:
			fprintf(stderr, "Received SIGHUP, restarting relaying...\n");
			if (manager) {manager->stop_relaying();}
			if (manager) {manager->start_control_relaying();}
			break;
	}
}

extern "C" int main(int argc, char **argv)
{
	int opt;
	char *host;
	bool client=false, server=false, device_set=false, host_set=false;
	FILE *keylog_output_file = NULL;

	struct sigaction action;
	memset(&action, 0, sizeof(struct sigaction));
	action.sa_handler = handle_signal;
	sigaction(SIGTERM, &action, NULL);
	sigaction(SIGHUP, &action, NULL);
	sigaction(SIGINT, &action, NULL);
	
	ConfigParser *cfg = new ConfigParser();

	while ((opt = getopt (argc, argv, "v:p:P:D:H:dsc:C:lmik::w:hxyzbgujVnq56")) != EOF) {
		switch (opt) {
		case 'v':
			cfg->set("vendorId", optarg);
			break;
		case 'p':
			cfg->set("productId", optarg);
			break;
		case 'P':
			cfg->add_to_vector("Plugins", optarg);
			break;
		case 'D':
			cfg->set("DeviceProxy", optarg);
			device_set = true;
			break;
		case 'H':
			cfg->set("HostProxy", optarg);
			host_set = true;
			break;
		case 'd':		/* verbose */
			debug++;
			cfg->debugLevel = debug;
			break;
		case 's':
			server=true;
			break;
		case 'c':
			client=true;
			host = optarg;
			break;
		case 'C':
			cfg->parse_file(optarg);
			break;
		case 'l':
			cfg->add_to_vector("Plugins", "PacketFilter_StreamLog");
			cfg->add_pointer("PacketFilter_StreamLog::file", stderr);
			break;
		case 'm':
			// Will be added to both filter and injector lists
			cfg->add_to_vector("Plugins", "PacketFilter_MassStorage");
			break;
		case 'i':
			cfg->add_to_vector("Plugins", "Injector_UDP");
			cfg->set("Injector_UDP::Port", "12345");
			break;
		case 'k':
			cfg->add_to_vector("Plugins", "PacketFilter_KeyLogger");
			if (optarg) {
				keylog_output_file = fopen(optarg, "r+");
				if (keylog_output_file == NULL) {
					fprintf(stderr, "Output file %s failed to open for writing, exiting\n", optarg);
					return 1;
				}
				fprintf(stderr, "Output file %s opened.\n", optarg);
				cfg->add_pointer("PacketFilter_KeyLogger::file", keylog_output_file);
			} else {
				cfg->add_pointer("PacketFilter_KeyLogger::file", stderr);
			}
			cfg->add_to_vector("Plugins", "PacketFilter_ROT13");
			break;
		case 'w':
			cfg->add_to_vector("Plugins", "PacketFilter_PcapLogger");
			cfg->set("PacketFilter_PcapLogger::Filename", optarg);
			break;
		case 'x':
			cfg->add_to_vector("Plugins", "PacketFilter_Xbox");
			cfg->add_pointer("PacketFilter_Xbox::file", stdout);
			cfg->set("DeviceProxy", "DeviceProxy_Xbox");
			device_set = true;
			cfg->set("HostProxy", "HostProxy_Xbox");
			host_set = true;
			//cfg->add_to_vector("Plugins", "Injector_UDPHID");
			//cfg->set("Injector_UDP::port", "12345");
			//cfg->add_to_vector("Plugins", "PacketFilter_UDPHID");
			break;
		case 'y':
			cfg->add_to_vector("Plugins", "PacketFilter_PSClassic");
			cfg->add_pointer("PacketFilter_PSClassic::file", stdout);
			break;
		case 'z':
			cfg->add_to_vector("Plugins", "PacketFilter_Switch");
			cfg->add_pointer("PacketFilter_Switch::file", stdout);
			cfg->set("HostProxy", "HostProxy_Switch");
			host_set = true;
			break;
		case 'g':
			cfg->add_to_vector("Plugins", "PacketFilter_NeoGeo");
			cfg->add_pointer("PacketFilter_NeoGeo::file", stdout);
			cfg->set("DeviceProxy", "DeviceProxy_NeoGeo");
			device_set = true;
			break;
		case 'b':
			cfg->add_to_vector("Plugins", "PacketFilter_Xbox360");
			cfg->add_pointer("PacketFilter_Xbox360::file", stdout);
			cfg->set("DeviceProxy", "DeviceProxy_Xbox360");
			device_set = true;
			break;
		case 'u':
			cfg->add_to_vector("Plugins", "PacketFilter_PS3");
			cfg->add_pointer("PacketFilter_PS3::file", stdout);
			cfg->set("DeviceProxy", "DeviceProxy_PS3");
			device_set = true;
			cfg->set("HostProxy", "HostProxy_PS3");
			host_set = true;
			break;
		case 'j':
			cfg->add_to_vector("Plugins", "PacketFilter_TG16Mini");
			cfg->add_pointer("PacketFilter_TG16Mini::file", stdout);
			break;
		case 'V':
			cfg->add_to_vector("Plugins", "PacketFilter_VCS");
			cfg->add_pointer("PacketFilter_VCS::file", stdout);
			break;
		case 'n':
			cfg->add_to_vector("Plugins", "PacketFilter_EVS");
			cfg->add_pointer("PacketFilter_EVS::file", stdout);
			cfg->set("DeviceProxy", "DeviceProxy_EVS");
			device_set = true;
			break;
		case '5':
			cfg->add_to_vector("Plugins", "PacketFilter_A500");
			cfg->add_pointer("PacketFilter_A500::file", stdout);
			break;
		case 'q':
			cfg->add_to_vector("Plugins", "PacketFilter_PS4");
			cfg->add_pointer("PacketFilter_PS4::file", stdout);
			cfg->set("DeviceProxy", "DeviceProxy_PS4");
			device_set = true;
			break;
		case '6':
			cfg->add_to_vector("Plugins", "PacketFilter_Switch");
			cfg->add_pointer("PacketFilter_Switch::file", stdout);
			cfg->set("HostProxy", "HostProxy_GenMini");
			host_set = true;
			break;
		case 'h':
		default:
			usage(argv[0]);
			return 1;
		}
	}

	if (debug) {
		std::cerr << "Version " VERSION << '\n';
		struct utsname sysinfo;
		uname(&sysinfo);
		std::cerr << "Running under kernel "<< sysinfo.release << '\n';
	}

	if (client) {
		cfg->set("DeviceProxy", "DeviceProxy_LibUSB");
		cfg->set("HostProxy", "HostProxy_TCP");
		cfg->set("HostProxy_TCP::TCPAddress", host);
	} else if(server) {
		cfg->set("DeviceProxy", "DeviceProxy_TCP");
		cfg->set("HostProxy", "HostProxy_GadgetFS");
	} else {
		if(!device_set)
			cfg->set("DeviceProxy", "DeviceProxy_LibUSB");
		if(!host_set)
			cfg->set("HostProxy", "HostProxy_GadgetFS");
	}

	int status;
	do {
		manager=new Manager(debug);
		manager->load_plugins(cfg);
		cfg->print_config();

		manager->start_control_relaying();
		while ( ( status = manager->get_status()) == USBM_RELAYING) {
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}

		manager->stop_relaying();
		manager->cleanup();
		delete(manager);
	} while ( status == USBM_RESET);
	
	if (keylog_output_file) {
		fclose(keylog_output_file);
	}

	printf("done\n");
	return 0;
}
