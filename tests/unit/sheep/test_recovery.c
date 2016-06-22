#include <stdlib.h>
#include <unity.h>
#include <cmock.h>

#include "sheep_priv.h"
/* need for work_queue */
#include "work.h"
#include "event.h"
/* define at sheep/sheep.c */
#define EPOLL_SIZE 4096

static void test_start_recovery()
{
	struct vnode_info cur_vinfo;
	struct vnode_info old_vinfo;
	bool epoch_lifted = false;
	bool wildcard = false;
	struct system_info __sys;

	/* parameter set */
	sys = &__sys;
	__sys.gateway_only = false;
	__sys.this_node.nr_vnodes = 0;
	__sys.cinfo.flags = SD_CLUSTER_FLAG_AVOID_DISKFULL;
	__sys.ninfo.store[0] = 'p';
	__sys.ninfo.store[1] = 'l';
	__sys.ninfo.store[2] = 'a';
	__sys.ninfo.store[3] = 'i';
	__sys.ninfo.store[4] = 'n';
	__sys.ninfo.store[5] = '\0';

	/* create work queue */
	init_event(EPOLL_SIZE);
	init_work_queue(NULL);
	sys->recovery_wqueue = create_work_queue("rw", WQ_UNLIMITED);

	INIT_LIST_HEAD(&sys->req_wait_queue);

static struct store_driver plain_store = {
    .id = PLAIN_STORE,
    .name = "plain",
/*
    .init = default_init,
    .exist = default_exist,
    .create_and_write = default_create_and_write,
    .write = default_write,
    .read = default_read,
    .link = default_link,
    .update_epoch = default_update_epoch,
    .cleanup = default_cleanup,
    .format = default_format,
    .remove_object = default_remove_object,
    .get_hash = default_get_hash,
    .purge_obj = default_purge_obj,
*/
};

list_add(&plain_store.list, &store_drivers);


	init_store_driver(true);

	TEST_ASSERT_EQUAL_HEX8(0, start_recovery(&cur_vinfo, &old_vinfo, epoch_lifted, wildcard));
}

int main(int argc, char **argv)
{
	UNITY_BEGIN();

	RUN_TEST(test_start_recovery);

	return UNITY_END();
}
