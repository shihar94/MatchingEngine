#ifndef KAFKAPUBLISHER_H
#define KAFKAPUBLISHER_H


#include <librdkafka/rdkafka.h>
#include <librdkafka/rdkafkacpp.h>


class kafkaPublisher
{
    public:
        RdKafka::Producer *m_producer;
        std::string m_topicName;
        int32_t m_topicPartition;
        std::string m_directory;
        RdKafka::Conf &m_globalCfg;
        std::string m_fileName; 
        uint64_t m_totalMsgCount = 0;
        //std::fstream file; 
        //std::vector<KafkaMessage> m_msgMap;
        //Log* m_loggingInst = NULL;

    public:
        kafkaPublisher();
        kafkaPublisher(const std::string &topicName, int32_t topicPartition,std::string& directory , const RdKafka::Conf &globalCfg);
        ~kafkaPublisher();
        void produce();
};


#endif
