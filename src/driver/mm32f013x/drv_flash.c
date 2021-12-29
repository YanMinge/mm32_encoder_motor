#include "drv_flash.h"
#include "hal_conf.h"

usr_config_data_type usr_config_data = {0x11};

int8_t write_usr_config(usr_config_data_type usr_config_data)
{
	FLASH_Status status;
    // Porgram FLASH Bank1
    // Unlock the Flash Bank1 Program Erase controller
    FLASH_Unlock();

    // Clear All pending flags
    FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);

    FLASH_ErasePage(BANK1_WRITE_START_ADDR);

    FLASH_ClearFlag(FLASH_FLAG_EOP );

    status = FLASH_ProgramWord(BANK1_WRITE_START_ADDR, usr_config_data.device_id);

    FLASH_ClearFlag(FLASH_FLAG_EOP );

    FLASH_Lock();
    
    (void)status;
    if((*(volatile uint32_t*) BANK1_WRITE_START_ADDR) != usr_config_data.device_id) {
        return -1;
    }
    return 0;
}

void load_usr_config(void)
{
    usr_config_data.device_id = (*(volatile uint32_t*) BANK1_WRITE_START_ADDR) & 0x000000ff;
}