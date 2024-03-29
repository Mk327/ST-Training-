#define _LARGEFILE64_SOURCE
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <inttypes.h>

typedef struct {
	uint8_t status;
	uint8_t first_chs[3];
	uint8_t partition_type;
	uint8_t last_chs[3];
	uint32_t lba;
	uint32_t sector_count;
} PartitionEntry;

int main(int argc, char **argv)
{
	char buf[512];

	int fd = open(argv[1], O_RDONLY);

	read(fd, buf, 512);

	uint32_t extended_lba = 0;

	PartitionEntry *table_entry_ptr = (PartitionEntry *) & buf[446];

	printf("%-5s %-10s %-10s %-10s %-10s %-10s %-10s %-10s\n", "Device",
			"Boot", "Start", "End", "Sectors", "Size", "Id", "Type");

	for (int i = 0; i < 4; i++) {
		printf("%s%-5d %-10c %-10u %-10u %-10u %uG      %-10X\n",
				argv[1],
				i + 1,
				table_entry_ptr[i].status == 0x80 ? '*' : ' ',
						table_entry_ptr[i].lba,
						table_entry_ptr[i].lba + table_entry_ptr[i].sector_count - 1,
						table_entry_ptr[i].sector_count,
						(uint32_t) (((uint64_t) table_entry_ptr[i].sector_count *
								512) / (1024 * 1024 * 1024)),
								table_entry_ptr[i].partition_type);
		/*Check if it an extended partition */
		if (table_entry_ptr[i].partition_type == 5)
		{
			extended_lba  = table_entry_ptr[i].lba;
		}
	}

	/* If it an extended partition */
	if (extended_lba != 0) {
		/* Use seek to open the offseted file  */
		lseek64(fd, (off64_t) extended_lba * 512, SEEK_SET);
		read(fd, buf, 512);
		table_entry_ptr = (PartitionEntry *) & buf[446];
		int j = 5;
		printf("%s%-5d %-10c %-10u %-10u %-10u %0.1fG      %-10X\n",
				argv[1],
				j,
				table_entry_ptr[0].status == 0x80 ? '*' : ' ',
						table_entry_ptr[0].lba + extended_lba,
						table_entry_ptr[0].lba + table_entry_ptr[0].sector_count -
						1 + extended_lba, table_entry_ptr[0].sector_count,
						(double) ((uint64_t) table_entry_ptr[0].sector_count *
								512) / (1024 * 1024 * 1024),
								table_entry_ptr[0].partition_type);
		j++;
		while (1) {
			/* Check if the partitions finished or not */
			if (table_entry_ptr[1].lba == 0) {
				break;
			}
			off64_t offset = extended_lba + table_entry_ptr[1].lba;
			lseek64(fd, (off64_t) offset * 512, SEEK_SET);
			read(fd, buf, 512);
			table_entry_ptr = (PartitionEntry *) & buf[446];
			printf("%s%-5d %-10c %-10lu %-10lu %-10u %0.1fG      %-10X\n",
					argv[1],
					j,
					table_entry_ptr[0].status == 0x80 ? '*' : ' ',
							table_entry_ptr[0].lba + offset,
							table_entry_ptr[0].lba +
							table_entry_ptr[0].sector_count - 1 + offset,
							table_entry_ptr[0].sector_count,
							(double) ((uint64_t) table_entry_ptr[0].sector_count *
									512) / (1024 * 1024 * 1024),
									table_entry_ptr[0].partition_type);
			j++;
		}
	}

	return 0;
}
