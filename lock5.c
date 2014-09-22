#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

const char *lock_file = "/tmp/test_lock";

int main()
{
    int file_desc;
    struct flock region_to_lock;
    int res;

    file_desc = open(lock_file, O_RDWR | O_CREAT, 0666);

    if (!file_desc)
    {
        fprintf(stderr, "Unable to open %s for read/write\n", lock_file);
        exit(EXIT_FAILURE);
    }

    region_to_lock.l_type   = F_RDLCK; // 共享锁
    region_to_lock.l_whence = SEEK_SET;
    region_to_lock.l_start  = 10;
    region_to_lock.l_len    = 5;

    printf("Process %d, trying F_RDLCK, region %d to %d\n", getpid(),
            (int)region_to_lock.l_start,
            (int)region_to_lock.l_start + (int)region_to_lock.l_len);

    res = fcntl(file_desc, F_SETLK, &region_to_lock);

    if (-1 == res)
    {
        printf("Process %d - failed to lock region\n", getpid());
    }
    else
    {
        printf("Process %d - obtained lock region\n", getpid());
    }

    region_to_lock.l_type   = F_UNLCK; // 去锁
    region_to_lock.l_whence = SEEK_SET;
    region_to_lock.l_start  = 10;
    region_to_lock.l_len    = 5;

    printf("Process %d, trying F_UNLCK, region %d to %d\n", getpid(),
            (int)region_to_lock.l_start,
            (int)region_to_lock.l_start + (int)region_to_lock.l_len);

    res = fcntl(file_desc, F_SETLK, &region_to_lock);

    if (-1 == res)
    {
        printf("Process %d - failed to unlock region\n", getpid());
    }
    else
    {
        printf("Process %d - unlocked region\n", getpid());
    }

    region_to_lock.l_type   = F_UNLCK; // 去锁
    region_to_lock.l_whence = SEEK_SET;
    region_to_lock.l_start  = 0;
    region_to_lock.l_len    = 50;

    printf("Process %d, trying F_UNLCK, region %d to %d\n", getpid(),
            (int)region_to_lock.l_start,
            (int)region_to_lock.l_start + (int)region_to_lock.l_len);

    res = fcntl(file_desc, F_SETLK, &region_to_lock);

    if (-1 == res)
    {
        printf("Process %d - failed to lock region\n", getpid());
    }
    else
    {
        printf("Process %d - unlocked region\n", getpid());
    }

    region_to_lock.l_type   = F_WRLCK; // 去锁
    region_to_lock.l_whence = SEEK_SET;
    region_to_lock.l_start  = 16;
    region_to_lock.l_len    = 5;

    printf("Process %d, trying F_WRLCK, region %d to %d\n", getpid(),
            (int)region_to_lock.l_start,
            (int)region_to_lock.l_start + (int)region_to_lock.l_len);

    res = fcntl(file_desc, F_SETLK, &region_to_lock);

    if (-1 == res)
    {
        printf("Process %d - failed to lock region\n", getpid());
    }
    else
    {
        printf("Process %d - obtained lock on region\n", getpid());
    }

    region_to_lock.l_type   = F_RDLCK; // 共享锁
    region_to_lock.l_whence = SEEK_SET;
    region_to_lock.l_start  = 40;
    region_to_lock.l_len    = 10;

    printf("Process %d, trying F_RDLCK, region %d to %d\n", getpid(),
            (int)region_to_lock.l_start,
            (int)region_to_lock.l_start + (int)region_to_lock.l_len);

    res = fcntl(file_desc, F_SETLK, &region_to_lock);

    if (-1 == res)
    {
        printf("Process %d - failed to lock region\n", getpid());
    }
    else
    {
        printf("Process %d - obtained lock on region\n", getpid());
    }

    region_to_lock.l_type   = F_WRLCK; // 独占锁
    region_to_lock.l_whence = SEEK_SET;
    region_to_lock.l_start  = 16;
    region_to_lock.l_len    = 5;

    printf("Process %d, trying F_WRLCK with wait, region %d to %d\n", getpid(),
            (int)region_to_lock.l_start,
            (int)region_to_lock.l_start + (int)region_to_lock.l_len);

    res = fcntl(file_desc, F_SETLKW, &region_to_lock);

    if (-1 == res)
    {
        printf("Process %d - failed to lock region\n", getpid());
    }
    else
    {
        printf("Process %d - obtained lock on region\n", getpid());
    }

    printf("Process %d ending\n", getpid());

    close(file_desc);
    exit(EXIT_SUCCESS);
}

