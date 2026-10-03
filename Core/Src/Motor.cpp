//
// Created by qjy on 2026/10/3.
//
#include "Motor.hpp"
#include "string.h"
//1.折8字节为字段（字节序+符号）
void Motor::canRxMSgCallback(const uint8_t rx_data[8]) {
    uint16_t ecd_angle =(rx_data[0]<<8)|rx_data[1];
    int8_t speed_rpm=(rx_data[2]<<8)|rx_data[3];
    int8_t currentA=(rx_data[4]<<8)|rx_data[5];
    uint8_t tempC=rx_data[6];


    //2.角度换算
    ecd_angle =ecd_angle*360/8192;
    speed_rpm =speed_rpm;
    uint8_t currentA_=currentA*20/16384;
    tempC     = tempC;
    //3.环形

    if (received_ == false) {
        last_ecd_=ecd_angle;
        received_=true;
    }

    uint16_t diff=ecd_angle-last_ecd_;
    if (diff > (kEncoderRange /2)) {
        diff -= kEncoderRange;
    }else if (diff < -(kEncoderRange / 2)) {
        diff += kEncoderRange;
    }
    //4.
    float diff_angle=diff*360/kEncoderRange;
    angle_+=(diff_angle/ratio_);
}
void Motor::setTxCurrent(float amperes,uint8_t motor_id) {
    if (amperes > 20.0) {
        currentA_=20;
        int16_t currentA_=int16_t(amperes*16384/20);

    }
    else if (amperes < -20.0) {
        currentA_=-20.0;
        int16_t currentA_=int16_t(amperes*16384/20);
    }
    tx_data_[int8_t(index)]     = (currentA_ >> 8) & 0xFF;
    tx_data_[int8_t(index + 1)] = (currentA_) & 0xFF;

}
uint8_t Motor::getTXData(){
    return tx_data_[index];

}


