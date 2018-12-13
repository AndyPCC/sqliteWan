#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>

#define LOCK_MANAGER_HASHSIZE 256

struct lock_item {
	pthread_rwlock_t page_lock;
	int refcount;
	int pgno;
};

struct page_locks {
	int conn_nums;
	pthread_mutex_t conn_lock;
	pthread_mutex_t page1_lock;
	struct lock_item items[LOCK_MANAGER_HASHSIZE];
};

struct page_locks *lock_manager;

int main() {
	int shmid = shmget((key_t)55555, 16472, 0666|IPC_CREAT);
	printf("shmid = %d\n", shmid);

	void* memspace;
	memspace = shmat(shmid, NULL, 0);
	lock_manager = (struct page_lock*) memspace;
	printf("conn_nums = %d\n", lock_manager->conn_nums);
	printf("page[0], refcount= %d, pgno= %d\n", lock_manager->items[0].refcount, lock_manager->items[0].pgno);
	printf("page[255], refcount= %d, pgno= %d\n", lock_manager->items[255].refcount, lock_manager->items[255].pgno);


	return 0;
}
