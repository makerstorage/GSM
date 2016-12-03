
boolean auth_web(String myPhoneNumber){
String temp ="";
boolean result=false;

temp  = "GET http://m2m.makerstorage.com/index.php?phone="+myPhoneNumber+"\r\n";
temp.toCharArray(ip_data, 64) ;

//Serial.println("tcp message:");
//Serial.println(ip_data);

 // Selects Single-connection mode
    if (sendATcommand2("AT+CIPMUX=0", "OK", "ERROR", 1000) == 1)
    {
        // Waits for status IP INITIAL
        while(sendATcommand("AT+CIPSTATUS", "INITIAL", 500)  == 0 );
       // delay(100);
        
        snprintf(aux_str, sizeof(aux_str), "AT+CSTT=\"%s\",\"%s\",\"%s\"", apn, user_name, password);
         
        // Sets the APN, user name and password
        if (sendATcommand2(aux_str, "OK",  "ERROR", 30000) == 1)
        {            
            // Waits for status IP START
            while(sendATcommand("AT+CIPSTATUS", "START", 500)  == 0 );
            //delay(100);
            
            // Brings Up Wireless Connection
            if (sendATcommand2("AT+CIICR", "OK", "ERROR", 30000) == 1)
            {
                // Waits for status IP GPRSACT
                while(sendATcommand("AT+CIPSTATUS", "GPRSACT", 500)  == 0 );
                //delay(100);
                
                // Gets Local IP Address
                if (sendATcommand2("AT+CIFSR", ".", "ERROR", 10000) == 1)
                {
                    // Waits for status IP STATUS
                    while(sendATcommand("AT+CIPSTATUS", "IP STATUS", 500)  == 0 );
                   // delay(100);
                    //Serial.println("Opening TCP");
                    
                    snprintf(aux_str, sizeof(aux_str), "AT+CIPSTART=\"TCP\",\"%s\",\"%s\"", IP_address, port);
                    
                    // Opens a TCP socket
                    if (sendATcommand2(aux_str, "CONNECT OK", "CONNECT FAIL", 30000) == 1)
                    {
                       // Serial.println("Connected");
                        
                        // Sends some data to the TCP socket
                        sprintf(aux_str,"AT+CIPSEND=%d", strlen(ip_data));
                        if (sendATcommand2(aux_str, ">", "ERROR", 10000) == 1)    
                        {
                            sendATcommand2(ip_data, "SEND OK", "ERROR", 10000);
                          //  delay(100);
                            sim900_read_buffer(gprsBuffer,10,DEFAULT_TIMEOUT);
                            //Serial.println("serverdan cevap:");
                            //Serial.println(gprsBuffer);
                            if(NULL != strstr(gprsBuffer,"true")) {
                              result=true;
                            } else {result=false;}

                            sim900_clean_buffer(gprsBuffer,64);
                        }
                        
                        // Closes the socket
                        sendATcommand2("AT+CIPCLOSE", "CLOSE OK", "ERROR", 10000);
                    }
                    else
                    {
                        //Serial.println("Error opening the connection");
                    }  
                }
                else
                {
                    //Serial.println("Error getting the IP address");
                }  
            }
            else
            {
                //Serial.println("Error bring up wireless connection");
            }
        }
        else
        {
            //Serial.println("Error setting the APN");
        } 
    }
    else
    {
        //Serial.println("Error setting the single connection");
    }

    return result;
    
  
}
