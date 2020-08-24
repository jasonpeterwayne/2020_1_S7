import java.rmi.*;
import java.rmi.server.UnicastRemoteObject;
import java.util.Date;

public class RMIClientImpl2 extends UnicastRemoteObject implements RemoteDate
{
	 public RMIClientImpl2() throws RemoteException {  }

	 //Request function from other peer(RemoteDateImpl2)
	 //Generate current Date Information
	 public Date getDate() throws RemoteException {
	        return new Date();
	    }
	 public static void main(String args[]) {
		 try {
			 //Generate Server Object DateClientServer
			 RemoteDate DateClientServer = new RMIClientImpl2();
			//Bind this object instance to the name "DateClientServer"
			 Naming.rebind("DateClientServer", DateClientServer);
	            
			 System.out.println("DateClientServer bound in registry");
			 
			 //Host Name with Server Object(DateServer)
			 String host = "rmi://127.0.0.1/DateServer";
			 //Search the object with given host and save as 'dateServer'
			 RemoteDate dateServer = (RemoteDate)Naming.lookup(host);
			 //Invoke the function getDate() in RemoteDateImpl2
			 System.out.println(dateServer.getDate());
		 }
		 catch (Exception e) {
			 System.err.println(e);
		 }
	 }
}

