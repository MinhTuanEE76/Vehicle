## Overview
Dio Driver is responsible for:
- Configuring the direction of the GPIO pins
- Configuring the level of the GPIO pins
- Reading the level of the GPIO pins
- Toggling the level of the GPIO pins

## Features
- GPIO pin direction configuration
- GPIO pin level configuration
- GPIO pin level reading
- GPIO pin level toggling

## Public APIs
| API                       |                                  Description                                |
|-----                      |-----------------------------------------------------------------------------|
| Dio_Init                  | Initialize Dio module                                                       |
| Dio_WriteChannel          | Write value to a GPIO channel                                               |
| Dio_ReadChannel           | Read value from a GPIO channel                                              |
| Dio_FlipChannel           | Toggle the value of a GPIO channel                                          |


## Notes
Truy cập GPIO port thông qua con trỏ đến thanh ghi của port đó. Mỗi port có một địa chỉ base khác nhau, nên cần một bảng ánh xạ các con trỏ đến các thanh ghi của các port.
static GPIO_Reg_TypeDef_t* GPIO_Ports_Table[] = 
{
    GPIOA,
    GPIOB,
    GPIOC,
    GPIOD,
    GPIOE,
    GPIOF,
    GPIOG,
    GPIOH
};

#define DIO_CHANNEL_ID(GROUP, CHANNEL)  (Dio_ChannelType)((GROUP << 8) | CHANNEL) để xác định một channel cụ thể trong một port cụ thể. GROUP là số thứ tự của port (0-7), CHANNEL là số thứ tự của pin trong port (0-15).