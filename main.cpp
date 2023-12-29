#include <stdio.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <net/if.h>
#include <sys/kern_event.h>

int main(int argc,char** argv) {
   // create a socket of type PF_SYSTEM to listen for events
   int s = socket(PF_SYSTEM, SOCK_RAW, SYSPROTO_EVENT);
   // make sure we get receive the correct events
   kev_request key;
   key.vendor_code = KEV_VENDOR_APPLE;
   key.kev_class = KEV_NETWORK_CLASS;
   key.kev_subclass = KEV_ANY_SUBCLASS;
   //
   int code = ioctl(s, SIOCSKEVFILT, &key);
   kern_event_msg msg;
   // endless loop
   while(1) {
        // get notification
        code = recv(s, &msg, sizeof(msg), 0);
        // check type of event
        switch(msg.event_code) {
           case KEV_DL_IF_DETACHED:
              // interface is detached
              break;
           case KEV_DL_IF_ATTACHED:
              // interface is attached
              break;
           case KEV_DL_LINK_OFF:
              // interface is turned off
              printf("link off\n");
              break;
           case KEV_DL_LINK_ON:
              // interface is turned on
              printf("link on\n");
              break;
        }
   }
   return 0;
}