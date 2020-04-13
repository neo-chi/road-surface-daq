/*******************************************************************************
 * @file	accelerometer.cpp
 * @author	reece chimento
 * @version	1.0
 * @since	2019-03-25
 * @see		https://github.com/reecechimento/road-surface-daq
*******************************************************************************/
#include "accelerometer.h"

/**
 * Default constructor.
 *
 * @note call begin() on this accelerometer to enable it.
 **/
Accelerometer::Accelerometer()
{
}

/**
 * Enables the accelerometer driver and configures this accelerometer.
 **/
void Accelerometer::begin() {
        Serial.printf("accelerometer: initializing...\n");
        _start_driver();
        _set_data_rate();
        _set_range();
        _enable_z_high_interrupt();
        Serial.printf("accelerometer: initialization complete!\n");
}

/**
 * Reads data into the specified buffer, given the context.
 *
 * @note PRE_IMPACT should be passed during regular operation.
 * @note POST_IMPACT should be passed on interrupt.
 *
 * @param buffer_to_write
 **/
void IRAM_ATTR Accelerometer::read(acc_buffer buffer_to_write)
{
        Serial.printf("accelerometer: reading...");
        switch (buffer_to_write) {
        case PRE_IMPACT:
                // fill impact[0 - 799]
                for (size_t i = 0; i < PRE_IMP_BUF_LEN; i++) {
                        driver.read();
                        impact[i].x = driver.x_g;
                        impact[i].y = driver.y_g;
                        impact[i].z = driver.z_g;
                }
                break;
        case POST_IMPACT:
                // fill impact[800 - 2399]
                for (size_t i = PRE_IMP_BUF_LEN; i < ACC_BUF_LEN; i++) {
                        driver.read();
                        impact[i].x = driver.x_g;
                        impact[i].y = driver.y_g;
                        impact[i].z = driver.z_g;
                }
                break;
        default:
                break;
        }
        Serial.printf("complete!\n");
}

/**
 * Reads a single accelerometer value and returns an acceleration structure.
 *
 * @returns acceleration struct
 **/
acceleration_data Accelerometer::read()
{
        driver.read();
        return {driver.x_g, driver.y_g, driver.z_g};
}

/**
 * Unlatch the interrupt, allowing the accelerometer to trigger interrupts
 * again.
 **/
void IRAM_ATTR Accelerometer::unlatch_interrupt()
{
        Serial.print("acclerometer: unlatching interrupt...");
        // Read the LIS3DH INT1SRC register. This unlatches the interrupt.
        Wire.beginTransmission(LIS3DH_DEFAULT_ADDRESS);
        Wire.write(LIS3DH_REG_INT1SRC);
        Wire.endTransmission();
        Wire.requestFrom(LIS3DH_DEFAULT_ADDRESS, 1);
        Wire.read();
        interrupt_has_occured = false;
        Serial.printf("complete!\n");
}

/**
 * Returns true if the accelerometer triggered an interrupt.
 *
 * @note return value is volatile because it can be modified at any point.
 *
 * @returns volatile bool
 **/
volatile bool IRAM_ATTR Accelerometer::interrupt_is_latched()
{
        if (interrupt_has_occured)
                return true;
        else
                return false;
}

/**
 * Sets the accelerometer driver's sampling rate and power mode.
 **/
void Accelerometer::_set_data_rate()
{
        switch (ACCELEROMETER_DATARATE) {
        case LIS3DH_DATARATE_LOWPOWER_1K6HZ:
                Serial.printf("accelerometer: setting data rate to low-power 1.6KHz...");
                Serial.printf("complete!\n");
                driver.setDataRate(ACCELEROMETER_DATARATE);
                break;
        case LIS3DH_DATARATE_LOWPOWER_5KHZ:
                Serial.printf("accelerometer: setting data rate to low-power 5.0KHz...");
                Serial.printf("complete!\n");
                driver.setDataRate(ACCELEROMETER_DATARATE);
                break;
        case LIS3DH_DATARATE_1_HZ:
                Serial.printf("accelerometer: setting data rate to 1Hz...");
                Serial.printf("complete!\n");
                driver.setDataRate(ACCELEROMETER_DATARATE);
                break;
        case LIS3DH_DATARATE_25_HZ:
                Serial.printf("accelerometer: setting data rate to 25Hz...");
                Serial.printf("complete!\n");
                driver.setDataRate(ACCELEROMETER_DATARATE);
                break;
        case LIS3DH_DATARATE_50_HZ:
                Serial.printf("accelerometer: setting data rate to 50Hz...");
                Serial.printf("complete!\n");
                driver.setDataRate(ACCELEROMETER_DATARATE);
                break;
        case LIS3DH_DATARATE_100_HZ:
                Serial.printf("accelerometer: setting data rate to 100Hz...");
                Serial.printf("complete!\n");
                driver.setDataRate(ACCELEROMETER_DATARATE);
                break;
        case LIS3DH_DATARATE_200_HZ:
                Serial.printf("accelerometer: setting data rate to 200Hz...");
                Serial.printf("complete!\n");
                driver.setDataRate(ACCELEROMETER_DATARATE);
                break;
        case LIS3DH_DATARATE_400_HZ:
                Serial.printf("accelerometer: setting data rate to 400Hz...");
                Serial.printf("complete!\n");
                driver.setDataRate(ACCELEROMETER_DATARATE);
                break;
        default:
                Serial.printf("accelerometer: ERROR... invalid data rate!");
                Serial.printf("failure!\n");
                break;
        }
}

/**
 * Sets the accelerometer driver's G detection range.
 **/
void Accelerometer::_set_range()
{
        switch(ACCELEROMETER_RANGE) {
        case LIS3DH_RANGE_2_G:
                Serial.printf("accelerometer: setting range to 2 G...");
                Serial.printf("complete!\n");
                break;
        case LIS3DH_RANGE_4_G:
                Serial.printf("accelerometer: setting range to 4 G...");
                Serial.printf("complete!\n");
                break;
        case LIS3DH_RANGE_8_G:
                Serial.printf("accelerometer: setting range to 8 G...");
                Serial.printf("complete!\n");
                break;
        case LIS3DH_RANGE_16_G:
                Serial.printf("accelerometer: setting range to 16 G...");
                Serial.printf("complete!\n");
                break;
        default:
                Serial.printf("accelerometer: ERROR... invalid range!");
                Serial.printf("failure!\n");
                break;
        }
        driver.setRange(ACCELEROMETER_RANGE);
}

/**
 * Enables Z HIGH interrupts and configures interrupt threshold, duration,
 * and latching.
 **/
void Accelerometer::_enable_z_high_interrupt()
{
        Serial.printf("accelerometer: enabling Z HIGH interrupt...");
        _write_register_8(LIS3DH_REG_INT1CFG, 0x20); // enable Z_HI interrupt
        Serial.printf("complete!\n");

        Serial.printf("accelerometer: setting interrupt threshold...");
        _write_register_8(LIS3DH_REG_INT1THS, 0x6F); // set a high threshold to trigger impact
        Serial.printf("complete!\n");

        Serial.printf("accelerometer: setting interrupt detection duration...");
        _write_register_8(LIS3DH_REG_INT1DUR, 0x03); // allow time to see interrupt
        Serial.printf("complete!\n");

        Serial.printf("accelerometer: enabling interrupts on pin INT1...");
        _write_register_8(LIS3DH_REG_CTRL3, 0x40);  // enable AOI on INT1
        Serial.printf("complete!\n");

        Serial.printf("accelerometer: enabling interrupt latching...");
        _write_register_8(LIS3DH_REG_CTRL5, 0x08);  // LATCH INTERRUPT ENABLE
        Serial.printf("complete!\n");
}

/**
 * Calls begin() on this accelerometer's driver.
 **/
void Accelerometer::_start_driver()
{
        Serial.printf("accelerometer: starting driver...");
        driver.begin();
        Serial.printf("complete!\n");
}

/**
 *  @param  reg register address
 *  @param  value value that will be written into selected register
 **/
void Accelerometer::_write_register_8(int reg, int value) {
        Wire.beginTransmission(LIS3DH_DEFAULT_ADDRESS);
        Wire.write(reg);
        Wire.write(value);
        Wire.endTransmission();
}

void IRAM_ATTR Accelerometer::populate_acceleration(acc_buffer buffer)
{
        switch (buffer) {
        case PRE_IMPACT:
                for (size_t i = 0; i < ACC_PRE_IMPACT_LEN; i++) {
                        driver.read();
                        acceleration->x[i] = driver.x_g;
                        acceleration->y[i] = driver.y_g;
                        acceleration->z[i] = driver.z_g;
                }
                break;
        case POST_IMPACT:
                for (size_t i = ACC_PRE_IMPACT_LEN; i < ACC_BUF_LEN; i++) {
                        driver.read();
                        acceleration->x[i] = driver.x_g;
                        acceleration->y[i] = driver.y_g;
                        acceleration->z[i] = driver.z_g;
                }
                break;
        default:
                break;
        }
}
