import java.rmi.*;
import java.rmi.server.UnicastRemoteObject;
import java.util.Date;

public class RemoteDateImpl2 extends UnicastRemoteObject implements RemoteDate
{
	public RemoteDateImpl2() throws RemoteException {  }
	
	//Request function from other peer(RMIClientImpl2)
	//Generate current Date Information
    public Date getDate() throws RemoteException {
        return new Date();
    }

    public static void main(String[] args)  {
        try {
        	//Generate Server Object DateServer
        	RemoteDate DateServer = new RemoteDateImpl2();
        	//Bind this object instance to the name "DateServer"
            Naming.rebind("DateServer", DateServer);
            
            System.out.println("DateServer bound in registry");
            
            //Host Name with Server Object(DateClientServer)
            String host = "rmi://127.0.0.1/DateClientServer";
            //Search the object with given host and save as 'dateClientServer'
            RemoteDate dateClientServer = (RemoteDate)Naming.lookup(host);
            //Invoke the function getDate() in RMIClientImpl2
            System.out.println(dateClientServer.getDate());
        }
        catch (Exception e) {
            System.err.println(e);
        }
    }  
}
