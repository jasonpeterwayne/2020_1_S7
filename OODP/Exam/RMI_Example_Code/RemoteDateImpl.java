import java.rmi.*;
import java.rmi.server.UnicastRemoteObject;
import java.util.Date;

public class RemoteDateImpl extends UnicastRemoteObject implements RemoteDate
{
    public RemoteDateImpl() throws RemoteException {  }

    public  Date getDate() throws RemoteException {
        return new Date();
    }

   public static void main(String[] args)  {
        try {

            RemoteDate dateServer = new RemoteDateImpl();

            Naming.rebind("DateServer", dateServer);

            System.out.println("DateServer bound in registry");
        }
        catch (Exception e) {
            System.err.println(e);
        }
    }



}
