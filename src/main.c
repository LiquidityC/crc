#include <getopt.h>
#include <stdio.h>
#include <string.h>

#include "common.h"

#include "crc16_ccitt_false.h"

#define MAX_DATA_LEN 1024

typedef enum crc_type {
	CRC_16_CCITT_FALSE,
	UNKNOWN,
} CrcType;

typedef struct CrcTypeEntry {
	const char *label;
	CrcType type;
	u64 (*compute)(const u8 *data, size_t len);
} CrcTypeEntry;

static const CrcTypeEntry crc_type_table[] = {
	{ "crc16-ccitt-false", CRC_16_CCITT_FALSE, crc16_ccitt_false_compute },
	{ NULL, UNKNOWN },
};

typedef struct rt {
	const CrcTypeEntry *entry;
	u8 data[MAX_DATA_LEN];
	size_t data_len;
} Rt;

static void print_usage(const char *name)
{
	printf("Usage: %s [options] <hex>\n", name);
	printf("\nOptions:\n");
	printf("  -h\t\t\tShow this help message and exit\n");
	printf("  -t <type>\t\tSpecify the CRC type. Default: crc16-ccitt-false\n");
	printf("  -l\t\t\tList all supported CRC types\n");
}

static void list_crc_types(void)
{
	const CrcTypeEntry *entry = crc_type_table;
	printf("Available CRC types:\n");
	while (entry->type != UNKNOWN) {
		printf("\t%s\n", entry->label);
		entry++;
	}
}

static const CrcTypeEntry *parse_type(const char *type)
{
	const CrcTypeEntry *entry = crc_type_table;
	while (entry->type != UNKNOWN) {
		if (strcmp(entry->label, type) == 0) {
			return entry;
		}
		entry++;
	}

	fprintf(stderr, "Unknown type: %s\n", type);
	return entry;
}

static int parse_args(Rt *rt, int argc, char *argv[])
{
	int opt;
	while ((opt = getopt(argc, argv, "hlt:")) != -1) {
		switch (opt) {
		case 'h':
			print_usage(argv[0]);
			return 0;
		case 't':
			rt->entry = parse_type(optarg);
			break;
		case 'l':
			list_crc_types();
			return 0;
		default:
			print_usage(argv[0]);
			return 1;
		}
	}

	rt->data_len = 0;
	for (size_t i = optind; i < argc; ++i) {
		if (strlen(argv[i]) % 2 != 0) {
			fprintf(stderr, "Invalid hex string: %s\n", argv[i]);
			return 1;
		}

		size_t len = strlen(argv[i]) / 2;
		if (len > MAX_DATA_LEN) {
			fprintf(stderr, "Data too long: %s\n", argv[i]);
			return 1;
		}

		for (size_t j = 0; j < len; ++j) {
			sscanf(argv[i] + j * 2, "%2hhx", &rt->data[j]);
		}
		rt->data_len = len;
	}

	if (rt->data_len == 0) {
		fprintf(stderr, "No data specified\n");
		return 1;
	}

	return 0;
}

int main(int argc, char *argv[])
{
	Rt rt = { NULL, { '\0' } };

	if (argc < 2) {
		print_usage(argv[0]);
		return 1;
	}

	if (parse_args(&rt, argc, argv) != 0) {
		return 1;
	}

	if (rt.entry == NULL) {
		rt.entry = parse_type("crc16-ccitt-false");
	}

	if (rt.data_len > 0) {
		printf("%lx\n", rt.entry->compute(rt.data, rt.data_len));
	}

	return 0;
}
