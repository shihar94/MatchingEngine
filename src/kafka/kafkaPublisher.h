#ifndef KAFKAPUBLISHER_H
#define KAFKAPUBLISHER_H


#include <librdkafka/rdkafka.h>
#include <librdkafka/rdkafkacpp.h>



class kafkaPublisher
{
    public:
        kafkaPublisher();
        ~kafkaPublisher();
        void produce();

    private:
        rd_kafka_t *producer;
        rd_kafka_conf_t *conf;
        char errstr[512];
};


#endif
