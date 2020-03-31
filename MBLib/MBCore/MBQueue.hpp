#ifndef	EYER_QUEUE_H
#define	EYER_QUEUE_H
#include "MBLinkedEle.hpp"

namespace MB {
    template <typename T>
    class MBQueue
    {
    private:
        MBLinkedEle<T> * head;
        MBLinkedEle<T> * rear;
        int size = 0;
    public:
        MBQueue(/* args */);
        ~MBQueue();
        bool isEmpty();
        int clear();
        int enQueue(const T& data);
        int deQueue(T& data);
        int getSize();
        int getHead(T& data);
    };

    template <typename T>
    int MBQueue<T>::clear()
    {
        MBLinkedEle<T>* temp;
        while (head != nullptr) {
            temp = head;
            head = temp->next;
            delete temp;
            temp = nullptr;
            size--;
        }
        return 0;
    }

    template <typename T>
    int MBQueue<T>::enQueue(const T& data)
    {
        MBLinkedEle<T> * newEle = new MBLinkedEle<T>(data);
        if (head == nullptr) {
            head = rear = newEle;
            size++;
        }else {
            rear->next = newEle;
            rear = newEle;
            size++;
        }
        return 0;
    }

    template <typename T>
    int MBQueue<T>::deQueue(T& data)
    {
        if (head == nullptr) {
            return -1;
        }

        MBLinkedEle<T> * temp = head;
        data = temp->data;
        head = temp->next;
        delete temp;
        temp = nullptr;
        size--;
        return 0;
    }

    template <typename T>
    bool MBQueue<T>::isEmpty() {
        return head == nullptr;
    }

    template <typename T>
    int MBQueue<T>::getSize() {
        return size;
    }


    template <typename T>
    MBQueue<T>::MBQueue()
    {
        head = nullptr;
        rear = nullptr;
    }

    template <typename T>
    MBQueue<T>::~MBQueue()
    {
        clear();
    }

    template <typename T>
    int MBQueue<T>::getHead(T& data)
    {
        return 0;
    }

}

#endif
