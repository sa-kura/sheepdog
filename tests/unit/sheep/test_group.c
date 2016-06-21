#include <stdlib.h>
#include <unity.h>
#include <cmock.h>

#include "sheep_priv.h"
/* need for work_queue */
#include "work.h"
#include "event.h"
/* define at sheep/sheep.c */
#define EPOLL_SIZE 4096

static void test_sd_accept_handler()
{
	struct sd_node joined = {0};
	struct rb_root nroot = {0};
	size_t nr_nodes = 1;
	struct cluster_info cinfo = {0};
	struct system_info __sys = {0};

	/* parameter set */
	sys = &__sys;
	__sys.this_node.nr_vnodes = 1;
	__sys.vdi_inuse[0] = 9;
	__sys.gateway_only = false;
	__sys.cinfo.status = SD_STATUS_OK;
	__sys.cinfo.flags |= SD_CLUSTER_FLAG_USE_LOCK;

	cinfo.proto_ver = SD_SHEEP_PROTO_VER;
	cinfo.epoch = 1;
	cinfo.nr_nodes = 1;
	cinfo.status = SD_STATUS_OK;
	cinfo.ctime = 100;
	cinfo.proto_ver = SD_SHEEP_PROTO_VER;

	joined.nid.addr[12]=127; 
	joined.nid.addr[13]=0; 
	joined.nid.addr[14]=0; 
	joined.nid.addr[15]=1; 
	joined.nid.port=3;

	/* create work queue */
	init_event(EPOLL_SIZE);
	init_work_queue(NULL);
	sys->block_wqueue = create_ordered_work_queue("block");

	/*
	init_config_file();
	*/
	init_config_path(".");

	/* to skip  call start_recovery() */
	set_cluster_shutdown(true); 
	set_cluster_config(&cinfo);

	/* test target */
	sd_accept_handler(&joined, &nroot, nr_nodes, &cinfo);

	printf("\n");
	printf("__sys.vdi_inuse[0]=%ld\n", __sys.vdi_inuse[0]);
}

int main(int argc, char **argv)
{
	UNITY_BEGIN();

	RUN_TEST(test_sd_accept_handler);

	return UNITY_END();
}
