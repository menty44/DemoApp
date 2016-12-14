
/***************************************************************************
 *                                  _   _ ____  _
 *  Project                     ___| | | |  _ \| |
 *                             / __| | | | |_) | |
 *                            | (__| |_| |  _ <| |___
 *                             \___|\___/|_| \_\_____|
 *
 * Copyright (C) 1998 - 2015, Daniel Stenberg, <daniel@haxx.se>, et al.
 *
 * This software is licensed as described in the file COPYING, which
 * you should have received as part of this distribution. The terms
 * are also available at https://curl.haxx.se/docs/copyright.html.
 *
 * You may opt to use, copy, modify, merge, publish, distribute and/or sell
 * copies of the Software, and permit persons to whom the Software is
 * furnished to do so, under the terms of the COPYING file.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 ***************************************************************************/
/* <DESC>
 * simple HTTP POST using the easy interface
 * </DESC>
 */
#include <stdio.h>
#include "curl/curl.h"
#include "ctosapi.h"
#include "cJSON.h"
#include <stdlib.h>
#include "Transaction.h"


char *amount;
char *cardnumber;
char *cardpin;
int validation=0;


int curlpostmain(void) {
    
    BYTE key;
    BYTE sBuf[128];
    
    {
        CURL *curl;
        CURLcode res;
        ClearScreen(4, 14);
        CTOS_LCDTPrintXY(5, 2, "Sending......");
        curl = curl_easy_init();
        if (curl) {
            char* jsonObj = "{ \"pin\" : \"4444\" , \"amount\" :\"1000\", \"card_number\" : \"72828276766262\" }"; 
            curl_easy_setopt(curl, CURLOPT_URL, "http://196.216.73.150:9990/posdemo/request/card");
            struct curl_slist *headers = NULL;
            headers = curl_slist_append(headers, "Accept: application/json");
            headers = curl_slist_append(headers, "Content-Type: application/json");
            headers = curl_slist_append(headers, "charsets: utf-8");
            /* example.com is redirected, so we tell libcurl to follow redirection */
            curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

            /* Perform the request, res will get the return code */
             curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonObj);
            res = curl_easy_perform(curl);
            //CTOS_LCDTPrintXY(4, 4, " Response is");
            /* Check for errors */
            if (res == CURLE_OK)
            {
//                ClearScreen(4, 14);
//                CTOS_LCDTPrintXY(4, 6, " Successful");
//                CTOS_KBDGet(&key);
                validation=1;
                return 1;
            }
            else
            {
//                ClearScreen(4, 14);
//                CTOS_LCDTPrintXY(4, 6, " Failed");
//                CTOS_KBDGet(&key);
                 validation=0;
                return 0;
            }
                CTOS_KBDGet(&key);
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));
            sprintf(sBuf, "%s     ", "ROAM");

            /* always cleanup */
            curl_easy_cleanup(curl);
        }
        CTOS_KBDGet(&key);
        curl_global_cleanup();

        CTOS_KBDGet(&key);
        return;
    }


}