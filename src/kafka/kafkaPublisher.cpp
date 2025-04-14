#include "kafkaPublisher.h"
#include <iostream>
kafkaPublisher::kafkaPublisher()
{
    std::cout <<1 << std::endl;
}
kafkaPublisher::kafkaPublisher(const std::string &topicName, int32_t topicPartition, std::string& directory, RdKafka::Conf *globalCfg)
{
    
    m_topicName = topicName;
    m_topicPartition = topicPartition;
    m_directory= directory;
    m_globalCfg = *globalCfg;
    
    m_fileName = m_directory + "/"+ m_topicName + "_" + std::to_string(m_topicPartition) +".dat";
    //m_loggingInst = Log::getLogInstance();
    
    try
    {
      //m_msgMap = fileReader::getMessages(m_fileName);
    }
    catch(const std::exception& e)
    {
      //EPrintf("Producer Initialization Failed %s\n" ,e.what());
    }
    
    //m_loggingInst->writeLog("Initialised Topic: %s Partition No:%d FileName: %s With Message Count of: %d\n",m_topicName.c_str(),m_topicPartition,m_fileName.c_str(),m_msgMap.size());
  
}

kafkaPublisher::~kafkaPublisher()
{
    m_producer->purge(RdKafka::Producer::PURGE_QUEUE);
    m_producer->flush(0);
    m_producer->poll(0);

    delete m_producer; 
    m_producer = nullptr;
    //m_loggingInst->writeLog("Producer terminated for :%s Partition No: %d\n",m_topicName.c_str(),m_topicPartition);
        
}

void kafkaPublisher::produce()
{
    std::string errstr;
            m_producer = RdKafka::Producer::create(m_globalCfg, errstr);

            if (!m_producer) 
            {
             // EPrintf("Failed to create producer: %s\n" ,errstr.c_str());
              exit(1);
            }

            int64_t msgCount  = 0;
            /*
            for(auto msg : m_msgMap)
            {

              auto msgPayload = msg.m_payload;
              int64_t msgLen = msg.m_msgLen;

              RdKafka::ErrorCode resp =m_producer->produce( m_topicName, 
                                                            m_topicPartition,
                                                          RdKafka::Producer::RK_MSG_COPY ,
                                                          const_cast<char*>(msgPayload), msgLen ,
                                                          NULL, 0,
                                                          0,
                                                          msg.m_headers,
                                                          NULL);

              if (resp != RdKafka::ERR_NO_ERROR) 
              {
                EPrintf("Produce failed:: %s\n" ,(RdKafka::err2str(resp)).c_str());
                msg.destroyHeaders();
              }
              
              m_producer->poll(100);
              msg.destroyMsg();
              msgCount++;
              
            }*/
            //m_loggingInst->writeLog("Completed Producing :%s fileName:%s With Message Count of:%d\n",m_producer->name().c_str(),m_fileName.c_str(),msgCount);
        
}