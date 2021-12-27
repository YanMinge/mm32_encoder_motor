#ifndef __DRV_FLASH_H__
#define __DRV_FLASH_H__

#include "stdint.h"

#define BANK1_WRITE_START_ADDR  ((uint32_t)0x08003000)

typedef struct
{
    uint32_t  device_id;
} usr_config_data_type;

extern usr_config_data_type usr_config_data;

int8_t write_usr_config(usr_config_data_type usr_config_data);
void load_usr_config(void);

#endif //__DEMO_H__