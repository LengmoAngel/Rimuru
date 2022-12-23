/* lfs_port.c */
#include "lfs.h"
#include "sfud.h"

       int lfs_flash_init(      struct lfs_config *c);
static int lfs_flash_read(const struct lfs_config *c, lfs_block_t block, lfs_off_t off, void *buffer, lfs_size_t size);
static int lfs_flash_prog(const struct lfs_config *c, lfs_block_t block, lfs_off_t off, const void *buffer, lfs_size_t size);
static int lfs_flash_erase(const struct lfs_config *c, lfs_block_t block);
static int lfs_flash_sync(const struct lfs_config *c);

int lfs_flash_init(struct lfs_config *c)
{
    sfud_init(); /* init sfud. */
    const sfud_flash *flash = sfud_get_device(0u);

    c->read = lfs_flash_read;
    c->prog = lfs_flash_prog;
    c->erase = lfs_flash_erase;
    c->sync = lfs_flash_sync;

    c->read_size = 16;
    c->prog_size = 16;
    //c->block_size = LFS_FLASH_SECTOR_SIZE;
    c->block_size = flash->chip.erase_gran;
    c->block_count = 256;
    c->block_cycles = 500;
    c->cache_size = 16;
    c->lookahead_size = 16;

    //c->read_buffer = (void *)lfs_flash_read_buf;
    //c->prog_buffer = (void *)lfs_flash_prog_buf;
    //c->lookahead_buffer = (void *)lfs_flash_lookahead_buf;


    return LFS_ERR_OK;
}

static int lfs_flash_read(const struct lfs_config *c, lfs_block_t block, lfs_off_t off, void *buffer, lfs_size_t size)
{
    uint32_t addr = block * c->block_size + off;
    const sfud_flash *flash = sfud_get_device(0u);

    sfud_read(flash, addr, size, (uint8_t *)buffer);
    return LFS_ERR_OK;
}

static int
lfs_flash_prog(const struct lfs_config *c, lfs_block_t block, lfs_off_t off, const void *buffer, lfs_size_t size)
{
    uint32_t addr = block * c->block_size + off;
    const sfud_flash *flash = sfud_get_device(0u);

    sfud_write(flash, addr, size, (uint8_t *)buffer);
    return LFS_ERR_OK;
}

static int lfs_flash_erase(const struct lfs_config *c, lfs_block_t block)
{
    const sfud_flash *flash = sfud_get_device(0u);

    sfud_erase(flash, block * c->block_size, c->block_size);
    return LFS_ERR_OK;
}

static int lfs_flash_sync(const struct lfs_config *c)
{
    return LFS_ERR_OK;
}


/* EOF. */
