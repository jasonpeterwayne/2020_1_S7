import java.util.Scanner;

public class FamilyBank_Demo {
	public static Family[] list = { new FM1(), new FM2(), new FM3(), new FM4(), new FM5(), new FM6() };
		
	// 4. Client creates "visitor" objects and passes each to accept() calls
	public static void main( String[] args ) {
		Storing    store   = new Storing();
		Retriving  retrieve = new Retriving();
		
		int maxBalance = 100;
		int inputBalance, inputFamilyMember;
		int ranNum = (int)(Math.random()*20)+10;
		int returnSValue, returnRValue;
		int totalSave = 0;
		int totalRecieve = 0;
		int count = 0;
		int ranFM;
		
		Scanner scan = new Scanner(System.in);
		
		do {
			System.out.println("Initial Balance : ");
			inputBalance = scan.nextInt();	
		} while(inputBalance > maxBalance);
		
		do {
			System.out.println("The number of Family Members : ");
			inputFamilyMember = scan.nextInt();	
		} while(inputFamilyMember > list.length);
			
		scan.close();
		System.out.println("initial Balance is " + inputBalance);
		
		//Appyling the object up
		//first dispatch
		while(true) {
			ranFM = (int)(Math.random()*inputFamilyMember);
			//form of polymorphic function
			list[ranFM].accept( store );
			returnSValue = list[ranFM].returnSValue( store );
			inputBalance += returnSValue;
			totalSave += returnSValue;
			//System.out.println("returnSValue is " + returnSValue);
			System.out.println("	New balance : " + inputBalance);
			
			ranFM = (int)(Math.random()*inputFamilyMember);
			
			list[ranFM].accept( retrieve );
			returnRValue = list[ranFM].returnValue( retrieve );
			
			if(returnRValue > inputBalance) {
				System.out.println("Not allowed, balance is not sufficient!");
				System.out.println("Total Saved: $" + totalSave + " Total Spent: $" + totalRecieve);
				System.out.println("Current balance : $" + inputBalance);
				count++;
			}
			else {
				totalRecieve += returnRValue;
				inputBalance -= returnRValue;
				System.out.println("	New balance : " + inputBalance);
			}
			
			if(count == 4)  break;
		}
	}
}
