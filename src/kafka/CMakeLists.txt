cmake_minimum_required(VERSION 3.15)

add_library(kafka kafkaPublisher.cpp kafkaPublisher.h kafkaDefs.h common.h)

install(TARGETS kafka DESTINATION lib)
install(FILES kafkaPublisher.h kafkaDefs.h common.h DESTINATION include)