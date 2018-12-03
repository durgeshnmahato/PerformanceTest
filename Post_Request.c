Post_Request()
{
	// Insert Step to execute
	/* Sample JSON to validate
	{
		"event":"ame_to_db",
		"inputs":
				{
					"file_id":"5bf3a0c38ae6ba001bb0e18f",
					"doc_id":"5bf3a0c48ae6ba001bb0e191",
					"doc_type":"model"
				}
	}
	*/

	int status_code;
	char *output_json;
	int i = 0;
	int is_valid_response = 1;
	
	char *expected_event = "ame_to_db";
	char *expected_file_id = "5bf3a0c38ae6ba001bb0e18f";
	char *expected_doc_id = "5bf3a0c48ae6ba001bb0e191";
	char *expected_doc_type= "model";
	
	lr_eval_json("Buffer/File=Request_Msg.json", 
	             "JsonObject=json_obj_2", LAST);
	
	lr_json_stringify("JsonObject=json_obj_2",
                                  "OutputParam=result",
                                LAST);
	lr_save_string(lr_eval_string("{result}"),"JsonReqFinal");
	
	lr_output_message("JSON  %s", lr_eval_string("{JsonReqFinal}"));
	i = lr_json_get_values("JsonObject=json_obj_2",
                "ValueParam=event_name",
                "QueryString=$.event",
                 LAST);
  	
  	//Compare the parameter value to the expected one
  	if(strcmp(lr_eval_string("{event_name}"), expected_event) != 0)
  	{
  		is_valid_response = 0;
  	}

  	lr_output_message("Event Name is %s", lr_eval_string("{event_name}"));
	
	/* Start Transcation with name "VALIDATE_RESPONSE" */
	lr_start_transaction ("VALIDATE_RESPONSE");
	
	/* reqister to get the entire Response Body message in a paramter "EntireBodyResponse"
	*This function should be set before making any web request*/
	
	web_reg_save_param("EntireBodyResponse","LB=","RB=","Search=Body",LAST);
	

	/* Send a HTTP GET request*/	
	web_rest("POST: http://localhost:9001/sbmit",
		"URL=http://localhost:9001/submit",
		"Method=POST",
		//"RecContentType=application/json",
		"Body={result}",
		"Snapshot=t511530.inf",
		HEADERS,
		"Name=Content-Type", "Value=application/json", ENDHEADER,
		LAST);

//	web_rest("POST: http://localhost:9001/submit",
//		"URL=http://localhost:9001/submit",
//		"Method=POST",
//		"EncType=raw",
//		"Snapshot=t901482.inf",
//		"Body=\t{\r\n"
//		"\t\t\"event\":\"ame_to_db\",\r\n"
//		"\t\t\"inputs\":\r\n"
//		"\t\t\t\t{\r\n"
//		"\t\t\t\t\t\"file_id\":\"5bf3a0c38ae6ba001bb0e18f\",\r\n"
//		"\t\t\t\t\t\"doc_id\":\"5bf3a0c48ae6ba001bb0e191\",\r\n"
//		"\t\t\t\t\t\"doc_type\":\"model\"\r\n"
//		"\t\t\t\t}\r\n"
//		"\t}",
//		HEADERS,
//		"Name=Content-Type", "Value=application/json", ENDHEADER,
//		LAST);

	/* Check the status code*/	
	status_code = web_get_int_property(HTTP_INFO_RETURN_CODE);
	
	/* Valdiate the status code*/
	if(status_code != 200)
	{
			/* End the trasaction and mark it FAIL*/
			lr_end_transaction("VALIDATE_RESPONSE", LR_FAIL);
			
			/* Exit, if it is required as soon as Trasaction is marked as FAIL*/
			lr_exit(LR_EXIT_VUSER, LR_FAIL);
	}

	/*Debug output message*/
	lr_output_message("Response JSON object is %s", lr_eval_string("{EntireBodyResponse}"));
	
	/*Store the value as string of parameter "EntoreBodyResponse"*/
  	output_json = lr_eval_string("{EntireBodyResponse}");
  	lr_output_message("After save to a string is %s", output_json);
  	
  	/*Save the string in paramter*/
  	lr_save_string(lr_eval_string(output_json), "JSON_Input_Param");
   
  	/* Convert a string to a JSON object */
   	lr_eval_json("Buffer={JSON_Input_Param}",
              "JsonObject=json_obj_1", LAST);	
  	
  	/* Find the value of specified filed $.event and store it in a paramter "event_param" for subsequent use */
	i = lr_json_get_values("JsonObject=json_obj_1",
                "ValueParam=event_name",
                "QueryString=$.event",
                 LAST);
  	
  	//Compare the parameter value to the expected one
  	if(strcmp(lr_eval_string("{event_name}"), expected_event) != 0)
  	{
  		is_valid_response = 0;
  	}

  	lr_output_message("Event Name is %s", lr_eval_string("{event_name}"));
  	
  	/* Find the value of specified filed $.inputs.file_id and store it in a paramter "event_param" for subsequent use */
  	i = lr_json_get_values("JsonObject=json_obj_1",
                "ValueParam=file_id",
                "QueryString=$.inputs.file_id",
                 LAST);  	
  	lr_output_message("File Id is %s", lr_eval_string("{file_id}"));
  	
  	//Compare the parameter value to the expected one
  	if(strcmp(lr_eval_string("{file_id}"), expected_file_id) != 0)
  	{
  		is_valid_response = 0;
  	}
  	
  	/* Find the value of specified filed $.inputs.doc_id and store it in a paramter "event_param" for subsequent use */
  	i = lr_json_get_values("JsonObject=json_obj_1",
                "ValueParam=doc_id",
                "QueryString=$.inputs.doc_id",
                 LAST);  	
  	lr_output_message("Doc Id is %s", lr_eval_string("{doc_id}"));
  	
  	//Compare the parameter value to the expected one
  	if(strcmp(lr_eval_string("{doc_id}"), expected_doc_id) != 0)
  	{
  		is_valid_response = 0;
  	}
  	
  	/* Find the value of specified filed $.inputs.doc_type and store it in a paramter "event_param" for subsequent use */
  	i = lr_json_get_values("JsonObject=json_obj_1",
                "ValueParam=doc_type",
                "QueryString=$.inputs.doc_type",
                 LAST);  	
  	lr_output_message("Doc type is %s", lr_eval_string("{doc_type}"));
  	
  	//Compare the parameter value to the expected one
  	if(strcmp(lr_eval_string("{doc_type}"), expected_doc_type) != 0)
  	{
  		is_valid_response =  0;
  	}
  	

	/* Mark the trasaction as "PASS" or "FAIL" based on the validation status*/  	
  	if(is_valid_response == 1)
  	{
  		  lr_end_transaction("VALIDATE_RESPONSE", LR_PASS);
  	}
  	else
  	{
  		  lr_end_transaction("VALIDATE_RESPONSE", LR_FAIL);
  	}

	return 0;
}
