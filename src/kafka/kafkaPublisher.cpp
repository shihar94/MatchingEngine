#include "kafkaPublisher.h"
#include <iostream>
#include "common.h"
#include "kafkaDefs.h"

#define ARR_SIZE(arr) ( sizeof((arr)) / sizeof((arr[0])) )
static void dr_msg_cb (rd_kafka_t *kafka_handle,
  const rd_kafka_message_t *rkmessage,
  void *opaque) {
if (rkmessage->err) {
std::cout<<"error" <<std::endl;
}
}

kafkaPublisher::kafkaPublisher()
{
    std::cout <<1 << std::endl;
    conf = rd_kafka_conf_new();

    // User-specific properties that you must set
    set_config(conf, KAFKA_BOOTSTRAP_SERVERS, "localhost:9092");

    // Fixed properties
    set_config(conf, "acks", "all");

    // Install a delivery-error callback.
    rd_kafka_conf_set_dr_msg_cb(conf, dr_msg_cb);

    // Create the Producer instance.
    producer = rd_kafka_new(RD_KAFKA_PRODUCER, conf, errstr, sizeof(errstr));
    if (!producer)
    {
        std::cout<<"error" <<std::endl;
        return;
    }
}


kafkaPublisher::~kafkaPublisher()
{
    rd_kafka_destroy(producer);
}

void kafkaPublisher::produce()
{
  // Produce data by selecting random values from these lists.
  int message_count = 10;
  const char *topic = "purchases";
  const char *user_ids[6] = {"eabara", "jsmith", "sgarcia", "jbernard", "htanaka", "awalther"};
  const char *products[5] = {"book", "alarm clock", "t-shirts", "gift card", "batteries"};

  for (int i = 0; i < message_count; i++) 
  {
      const char *key =  user_ids[random() % ARR_SIZE(user_ids)];
      const char *value =  products[random() % ARR_SIZE(products)];
      size_t key_len = strlen(key);
      size_t value_len = strlen(value);

      rd_kafka_resp_err_t err;

      err = rd_kafka_producev(producer,
                              RD_KAFKA_V_TOPIC(topic),
                              RD_KAFKA_V_MSGFLAGS(RD_KAFKA_MSG_F_COPY),
                              RD_KAFKA_V_KEY((void*)key, key_len),
                              RD_KAFKA_V_VALUE((void*)value, value_len),
                              RD_KAFKA_V_OPAQUE(NULL),
                              RD_KAFKA_V_END);

      if (err) 
      {
          std::cout<<"error" <<std::endl;
          return ;
      } else 
      {
          std::cout<<"error" <<std::endl;

      rd_kafka_poll(producer, 0);
      }
  }
  // Block until the messages are all sent.
  std::cout<<"error" <<std::endl;
  rd_kafka_flush(producer, 10 * 1000);

  if (rd_kafka_outq_len(producer) > 0)
  {
      std::cout<<"error" <<std::endl;
  }
}
