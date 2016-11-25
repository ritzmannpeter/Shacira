package org.ii.shacira.gatewayinterface;

public class cGatewayClient {
	cGatewayClient(String server_host, int server_port)
	{
		
	}
	public String Request(String request)
	{
		return request;
	}
	public String[] GetContextList()
	{
		String[] list = new String[50];
		return list;
	}
	public String GetValue(String cell_name, String var_spec)
	{
		return cell_name + "_" + var_spec;
		
	}
	void SetValue(String cell_name, String var_spec, String value)
	{
		
	}
}
