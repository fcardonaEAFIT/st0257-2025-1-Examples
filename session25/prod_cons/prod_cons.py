#!/usr/bin/env python

import logging
import time
from threading import Semaphore, Thread
import threading

size = 6
buffer = [0, 0, 0, 0, 0, 0]
entry = 0
outlet = 0
quantity = 0
    
def producer(mutex, full, empty,pId):
    global buffer, entry, outlet, size, quantity
    item = threading.local()
    item = 1

    logging.info("Start produce thread")
    while True:
        empty.acquire()
        mutex.acquire()
        buffer[entry] = (pId, item)
        entry = (entry + 1) % size
        quantity = quantity + 1
        logging.info("Produce item: %d", item)
        mutex.release()
        full.release()
        item = item + 1
        time.sleep(2)
        
def consumer(mutex, full, empty):
    global buffer, entry, outlet, size, quantity
    logging.info("Start consumer thread")
    while True:
        full.acquire()
        mutex.acquire()
        item = buffer[outlet]
        outlet = (outlet + 1) % size
        quantity = quantity - 1
        mutex.release()
        empty.release()
        # print(item)
        logging.info("Consumes item: %d from: %d", item[0], item[1])
        time.sleep(1)

if __name__ == "__main__":
    format = "%(asctime)s: %(message)s"
    logging.basicConfig(format=format, level=logging.INFO, datefmt="%H:%M:%S")
    mutex = Semaphore(1)
    full = Semaphore(0)
    empty = Semaphore(size)
    thread_producer_1 = Thread(target=producer,args=(mutex, full, empty,1))
    thread_producer_2 = Thread(target=producer,args=(mutex, full, empty,2))
    thread_consumer = Thread(target=consumer,args=(mutex, full, empty,))
    thread_producer_1.start()
    thread_producer_2.start()
    thread_consumer.start()
    thread_producer_1.join()
    thread_producer_2.join()
    thread_consumer.join()
                                           
                                        
