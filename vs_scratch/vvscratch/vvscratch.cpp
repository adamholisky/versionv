// vvscratch.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MAXBUFLEN 1000000

#define Elf32_Half uint16_t
#define Elf32_Word uint32_t
#define Elf32_Addr uint32_t
#define Elf32_Off uint32_t

#define EI_NIDENT 16

typedef struct {
    unsigned char e_ident[EI_NIDENT];
    Elf32_Half e_type;
    Elf32_Half e_machine;
    Elf32_Word e_version;
    Elf32_Addr e_entry;
    Elf32_Off e_phoff;
    Elf32_Off e_shoff;
    Elf32_Word e_flags;
    Elf32_Half e_ehsize;
    Elf32_Half e_phentsize;
    Elf32_Half e_phnum;
    Elf32_Half e_shentsize;
    Elf32_Half e_shnum;
    Elf32_Half e_shstrndx;
} Elf32_Ehdr;

typedef struct {
    Elf32_Word sh_name;
    Elf32_Word sh_type;
    Elf32_Word sh_flags;
    Elf32_Addr sh_addr;
    Elf32_Off sh_offset;
    Elf32_Word sh_size;
    Elf32_Word sh_link;
    Elf32_Word sh_info;
    Elf32_Word sh_addralign;
    Elf32_Word sh_entsize;
} Elf32_Shdr;

typedef struct {
    uint32_t	s_inodes_count;		/* Inodes count */
    uint32_t	s_blocks_count;		/* Blocks count */
    uint32_t	s_r_blocks_count;	/* Reserved blocks count */
    uint32_t	s_free_blocks_count;	/* Free blocks count */
    uint32_t	s_free_inodes_count;	/* Free inodes count */
    uint32_t	s_first_data_block;	/* First Data Block */
    uint32_t	s_log_block_size;	/* Block size */
    uint32_t	s_log_frag_size;	/* Fragment size */
    uint32_t	s_blocks_per_group;	/* # Blocks per group */
    uint32_t	s_frags_per_group;	/* # Fragments per group */
    uint32_t	s_inodes_per_group;	/* # Inodes per group */
    uint32_t	s_mtime;		/* Mount time */
    uint32_t	s_wtime;		/* Write time */
    uint16_t	s_mnt_count;		/* Mount count */
    uint16_t	s_max_mnt_count;	/* Maximal mount count */
    uint16_t	s_magic;		/* Magic signature */
    uint16_t	s_state;		/* File system state */
    uint16_t	s_errors;		/* Behaviour when detecting errors */
    uint16_t	s_minor_rev_level; 	/* minor revision level */
    uint32_t	s_lastcheck;		/* time of last check */
    uint32_t	s_checkinterval;	/* max. time between checks */
    uint32_t	s_creator_os;		/* OS */
    uint32_t	s_rev_level;		/* Revision level */
    uint16_t	s_def_resuid;		/* Default uid for reserved blocks */
    uint16_t	s_def_resgid;		/* Default gid for reserved blocks */
} ext2_super_block;

typedef struct {
	uint32_t	inode;			/* Inode number */
	uint16_t	rec_len;		/* Directory entry length */
	uint16_t	name_len;		/* Name length */
	char	    name[];			/* File name, up to EXT2_NAME_LEN */
} ext2_dir_entry;

typedef struct {
    uint32_t	bg_block_bitmap;		/* Blocks bitmap block */
    uint32_t	bg_inode_bitmap;		/* Inodes bitmap block */
    uint32_t	bg_inode_table;		/* Inodes table block */
    uint16_t	bg_free_blocks_count;	/* Free blocks count */
    uint16_t	bg_free_inodes_count;	/* Free inodes count */
    uint16_t	bg_used_dirs_count;	/* Directories count */
    uint16_t	bg_pad;
    uint32_t	bg_reserved[3];
} ext2_block_group_desc;

typedef struct {
    uint16_t	i_mode;		/* File mode */
    uint16_t	i_uid;		/* Low 16 bits of Owner Uid */
    uint32_t	i_size;		/* Size in bytes */
    uint32_t	i_atime;	/* Access time */
    uint32_t	i_ctime;	/* Creation time */
    uint32_t	i_mtime;	/* Modification time */
    uint32_t	i_dtime;	/* Deletion Time */
    uint16_t	i_gid;		/* Low 16 bits of Group Id */
    uint16_t	i_links_count;	/* Links count */
    uint32_t	i_blocks;	/* Blocks count */
    uint32_t	i_flags;	/* File flags */
    uint32_t    os_1_a;			/* OS dependent 1 */
    uint32_t	i_block[15]; /* Pointers to blocks <-- linux/ext2.h @ line 221 - 228 */
    uint32_t	i_generation;	/* File version (for NFS) */
    uint32_t	i_file_acl;	/* File ACL */
    uint32_t	i_dir_acl;	/* Directory ACL */
    uint32_t	i_faddr;	/* Fragment address */
    uint32_t    os_2_a;
    uint32_t    os_2_b;
    uint32_t    os_2_c;     /* OS dependent 2 */
} ext2_inode;


void elf_run(void);

int main()
{
    uint8_t * source = nullptr;
    long numbytes;

    Elf32_Ehdr* elf_header = nullptr;
    Elf32_Shdr* elf_sheader = nullptr;

    ext2_super_block* super_block = nullptr;

    uint32_t num_bytes_to_read = 1024 * 1024 * 400;

    FILE* fp = fopen("Y:\\versions\\v\\vs_scratch\\vvscratch\\Debug\\vv_hd.img", "r");

    if (fp != NULL) {
        fseek(fp, 0L, SEEK_END);
        numbytes = ftell(fp);

        fseek(fp, 0L, SEEK_SET);

        //source = (char*)calloc(numbytes, sizeof(char));
        source = (uint8_t *)calloc(num_bytes_to_read, sizeof(uint8_t));

        if (source == NULL) {
            printf("souce is null\n");
        }

        //fread(source, sizeof(char), numbytes, fp);
        fread(source, sizeof(uint8_t), num_bytes_to_read, fp);

        if (ferror(fp) != 0) {
            fputs("Error reading file\n", stderr);
        }

        printf("Total bytes read: 0x%08X\n",num_bytes_to_read);
        
        fclose(fp);
    }
    else {
        printf("fp is null\n");
    }

    if (source != NULL) {
        printf("00 and 01: %02X %02X\n", *(source), *(source + 1));
        printf("Should be 0x0000: %02X %02X\n", *(source + 0x1BC - 1), *(source + 0x1BD - 1));
        printf("Drive attrib: %02X\n", *(source + 0x1BE - 1));
        printf("parition type: %02X\n", *(source + 0x1BE + 0x4 - 1));
        printf("num sectors in partition: %02X %02X %02X %02X\n", *(source + 0x1BE + 0x0C - 1), *(source + 0x1BE + 0x0D - 1), *(source + 0x1BE + 0x0E - 1), *(source + 0x1BE + 0x0F - 1));

        uint32_t num_sectors = (*(source + 0x1BE + 0x0C - 1) << 24) + ((*(source + 0x1BE + 0x0D - 1)) << 16) + ((*(source + 0x1BE + 0x0E - 1)) << 8) + (*(source + 0x1BE + 0x0F - 1));

        uint32_t partition_start = *((uint32_t*)(source + 0x1BE + 0x8 - 1));
        uint32_t superblock_offset = (partition_start * 512) + 1024;

        printf("partition start:            %08X\n", partition_start);
        printf("num sectors little-endian:  %08X\n", *((uint32_t*)(source + 0x1BE + 0xC - 1)));
        printf("expecting superblock at:    %08X\n", superblock_offset);

        super_block = (ext2_super_block*)(source + superblock_offset);
        printf("lol magic? 0x%04X\n", super_block->s_magic);

        uint32_t block_size = 1024 << (super_block->s_log_block_size);
        printf("block size: 0x%08X\n", block_size);

        uint32_t num_block_groups = super_block->s_blocks_count / super_block->s_blocks_per_group;
        printf("num block groups: %d\n", num_block_groups);

        for (int z = 0; z < num_block_groups; z++) {
            uint32_t block_adjustment = (z > 0) ? (block_size + (sizeof(ext2_block_group_desc) * z)) : block_size;
            uint32_t blockgroup_offset = (partition_start * 512) + block_adjustment;

            ext2_block_group_desc* blockgroup = (ext2_block_group_desc*)(source + blockgroup_offset);

            printf("block of inode table: %d\n", blockgroup->bg_inode_table);
            printf("num directories: %d\n", blockgroup->bg_used_dirs_count);

            uint32_t inode_table_offset = (partition_start * 512) + (block_size * blockgroup->bg_inode_table);
            printf("inode table offset: 0x%08X\n", inode_table_offset);
            printf("free inodes: 0x%04X\n", blockgroup->bg_free_inodes_count);
            uint16_t num_inodes = super_block->s_inodes_per_group - blockgroup->bg_free_inodes_count;
            printf("num inodes in bg: %d / 0x%04X\n", num_inodes, num_inodes);

            for (int i = 0; i < num_inodes; i++) {
                ext2_inode* inode = (ext2_inode*)(source + inode_table_offset + (sizeof(ext2_inode) * i));
                ext2_dir_entry* dir = (ext2_dir_entry*)(source + (partition_start * 512) + (block_size * inode->i_block[0]));

                //printf("%02d: %04X", i + 1, (uint16_t)(inode->i_mode)); //i+1 b/c ext2 starts at 1

                if (inode->i_mode & 0x4000) {
                    printf("   dir");
                    printf("   start addr: 0x%08X\n", (uint32_t)((uint32_t*)(dir)));

                    uint16_t current_rec_length = 0xFFFF; // safety feature

                    do {
                        if (dir->inode != 0) {
                            dir->name[dir->name_len - 512] = 0;
                            printf("    Name: \"%s\"    \n    inode: %d    name_len: %d    rec len: 0x%04X    next addr: 0x%08X\n    -----\n", dir->name, dir->inode, dir->name_len - 512, dir->rec_len, (uint32_t)((uint32_t*)(dir)) + dir->rec_len);
                        }

                        current_rec_length = dir->rec_len;

                        dir = (ext2_dir_entry*)(((uint32_t)dir) + ((uint32_t)dir->rec_len));

                    } while ((current_rec_length & 0x0F00) == 0);

                    printf("\n");
                }

                if (inode->i_mode & 0x8000) {
                    // printf("   file");
                }
            }
        }
    }
}

void elf_run(void) {
    char* source = nullptr;
    long numbytes;

    Elf32_Ehdr* elf_header = nullptr;
    Elf32_Shdr* elf_sheader = nullptr;

    FILE* fp = fopen("vv_hd.img", "r");

    if (fp != NULL) {
        fseek(fp, 0L, SEEK_END);
        numbytes = ftell(fp);

        fseek(fp, 0L, SEEK_SET);

        source = (char*)calloc(numbytes, sizeof(char));

        if (source == NULL) {
            printf("souce is null\n");
        }

        fread(source, sizeof(char), numbytes, fp);

        if (ferror(fp) != 0) {
            fputs("Error reading file\n", stderr);
        }

        fclose(fp);
    }
    else {
        printf("fp is null\n");
    }

    if (source != NULL) {
        elf_header = (Elf32_Ehdr*)source;

        printf("source: 0x%08X\n", (uint32_t)source);
        printf("numbytes: 0x%08X\n", numbytes);

        printf("ehdr: 0x%x\n", sizeof(Elf32_Ehdr));
        printf("shdr: 0x%x\n", sizeof(Elf32_Shdr));

        printf("%s\n", elf_header->e_ident);

        printf("0x%X\n", elf_header->e_shoff);
        printf("0x%08X\n", (uint32_t)elf_header + elf_header->e_shoff);

        elf_sheader = (Elf32_Shdr*)((uint32_t)elf_header + elf_header->e_shoff);

        for (int i = 0; i < elf_header->e_shnum; i++) {
            printf("[%d / %x @ 0x%08X] %d    0x%08X    0x%08X\n", i, i, (uint32_t)&elf_sheader[i], elf_sheader[i].sh_type, elf_sheader[i].sh_addr, elf_sheader[i].sh_offset);
        }
    }

    printf("end\n");
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
