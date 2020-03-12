#include "mediator.h"
#include "data_collector.h"
#include "storage.h"
#include "uploader.h"

Mediator::Mediator() {

}

void Mediator::Update(data_collector_event event) {
  switch (event) {
    case data_collector_event::travel_buffer_full:
      // TODO: send String travel buffer to storage for write
      Serial.println("Received event: data_collector->travel_buffer_full");
      break;
    case data_collector_event::impact_buffer_full:
      // TODO: send String impact buffer to storage for write
      Serial.println("Received event: data_collector->impact_buffer_full");
      break;
    case data_collector_event::accelerometer_buffer_full:
      // TODO: send String accelerometer buffer to storage for write
      break;
    case data_collector_event::environment_buffer_full:
      // TODO: send String environment buffer to storage for write
      break;
    case data_collector_event::gps_satellite_connected:
      // TODO: set data_collector data collection behavior state
      break;
    case data_collector_event::gps_satellite_disconnected:
      // TODO: set data_collector data collection behavior state
      break;
    case data_collector_event::accelerometer_interrupt_latched:
      // if data_collector collection behavior state -> gps_satellite_connected
      //   send impact buffer to storage for writing
      //   wait for response
      // else if data_collector collection behavior state -> gps_statellite_disconnected
      //   send acceleration buffer to storage for writing
      //   wait for response
      break;
    case data_collector_event::accelerometer_interrupt_unlatched:
      // TODO: send String environment buffer to storage for write
      break;
    default:
      Serial.println("data_collector_event: unhandled case");
  }
}

void Mediator::Update(storage_event event) {
  switch ( event )
  {
    case storage_event::file_read_success:
    // TODO: Logic here
    Serial.println("storage_event->file_read_success");
    break;
    case storage_event::file_read_failure:
    // TODO: Logic here
    Serial.println("storage_event->file_read_failure");
    break;
    case storage_event::file_write_success:
    // TODO: Logic here
    Serial.println("storage_event->file_write_success");
    break;
    case storage_event::file_write_failure:
    // TODO: Logic here
    Serial.println("storage_event->file_write_failure");
    break;
    default:
    // TODO: Unhandled event
    Serial.println("storage_event->unhandled case");
    break;
  }
}

void Mediator::Update(uploader_event event) {
  switch ( event )
  {
    case uploader_event::upload_success:
    // TODO: Logic here
    Serial.println( "upload_event->upload_success" );
    break;
    case uploader_event::upload_failure:
    // TODO: Logic here
    Serial.println( "upload_event->upload_failure" );
    break;
    case uploader_event::wifi_connected:
    // TODO: Logic here
    Serial.println( "upload_event->wifi_connected" );
    break;
    case uploader_event::wifi_disconnected:
    // TODO: Logic here
    Serial.println( "upload_event->wifi_disconnected" );
    break;
    default:
    // TODO: Logic here
    Serial.println( "upload_event->unhandled case" );
    break;
  }
}