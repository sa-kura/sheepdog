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
	struct sd_node joined;
	struct rb_root nroot;
	size_t nr_nodes;
	struct cluster_info cinfo;
	struct system_info __sys;

	/* parameter set */
	sys = &__sys;
	__sys.this_node.nr_vnodes = 1;
	cinfo.proto_ver = SD_SHEEP_PROTO_VER;
	cinfo.ctime = 100;

	/* create work queue */
	init_event(EPOLL_SIZE);
	init_work_queue(NULL);
	sys->block_wqueue = create_ordered_work_queue("block");

	sd_accept_handler(&joined, &nroot, nr_nodes, &cinfo);
	printf("sys->node_status = %d\n", __sys.node_status);
}

int main(int argc, char **argv)
{
	UNITY_BEGIN();

	RUN_TEST(test_sd_accept_handler);

	return UNITY_END();
}
