package org.ii.shacira.gatewayinterface;

import org.ii.shacira.gatewayinterface.*;

public class Client {


/**
 * Runs main program.
 */
public static void main (String [] args) {
	cGatewayClient client = new cGatewayClient("winkie", 20000);
	String request;
	String reply;
	String value;
	String seppl = "heinz";
	int count = 0;
	while (true) {
		if (seppl == "heinz") {
			seppl = "fuzzy" + " " + count;
		} else {
			seppl = "heinz" + " " + count;
		}
		request = seppl;
		reply = client.Request(request);
		value = client.GetValue("seppl", seppl);
		System.out.print(value);
		System.out.println();
		count++;
	}
}
}

