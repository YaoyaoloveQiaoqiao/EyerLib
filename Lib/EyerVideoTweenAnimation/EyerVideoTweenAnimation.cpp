#include "EyerVideoTweenAnimation.hpp"
namespace Eyer
{
    EyerVideoTweenAnimation::EyerVideoTweenAnimation()
    {

    }
    EyerVideoTweenAnimation::~EyerVideoTweenAnimation()
    {

    }
    int EyerVideoTweenAnimation::GetLinearValue(double t, EyerVideoAnimationKey & outKey)
    {
        /*
        MB::MBLinkedList<MBTransKey*>* changeKeyList = new MB::MBLinkedList<MBTransKey*>();
        if (type == MBVideoChangeType::VIDEO_FRAGMENT_CHANGE_TRANS) {
            *changeKeyList = transKeyList;
        }
        else if (type == MBVideoChangeType::VIDEO_FRAGMENT_CHANGE_SCALE) {
            *changeKeyList = scaleKeyList;
        }

        if (changeKeyList->getLength() == 0) {
            x = 0;
            y = 0;
            z = 0;
            return 0;
        }

        MBLinkedEle<MB::MBTransKey*>* currentEle = changeKeyList->head;
        for (int i = 0; i < changeKeyList->getLength() - 1; i++) {
            MBLinkedEle<MB::MBTransKey*>* temp = currentEle->next;
            while (temp != nullptr) {
                if (temp->data->t < currentEle->data->t) {
                    MB::MBTransKey* data = currentEle->data;
                    currentEle->data = temp->data;
                    temp->data = data;
                }
                temp = temp->next;
            }
            if (currentEle->next != nullptr) {
                currentEle = currentEle->next;
            }
        }

        MB::MBTransKey* firstdata = nullptr;
        MB::MBTransKey* lastdata = nullptr;
        changeKeyList->find(0, firstdata);
        changeKeyList->find(changeKeyList->getLength() - 1, lastdata);

        if (t < firstdata->t) {
            x = firstdata->x;
            y = firstdata->y;
            z = firstdata->z;
            return 0;
        }
        else if (t > lastdata->t) {
            x = lastdata->x;
            y = lastdata->y;
            z = lastdata->z;
            return 0;
        }

        for (int i = 0; i < changeKeyList->getLength() - 1; i++) {
            changeKeyList->find(i, firstdata);
            changeKeyList->find(i + 1, lastdata);

            if (t >= firstdata->t && t < lastdata->t) {
                double tPart = (t - firstdata->t) / (lastdata->t - firstdata->t);
                x = tPart * (lastdata->x - firstdata->x) + firstdata->x;
                y = tPart * (lastdata->y - firstdata->y) + firstdata->y;
                z = tPart * (lastdata->z - firstdata->z) + firstdata->z;
                return 0;
            }
        }

        return 0;
        */
        return 0;
    }

    int EyerVideoTweenAnimation::AddKey(EyerVideoAnimationKey & key)
    {
        printf("int addkey\n");
        return 0;
    }

}