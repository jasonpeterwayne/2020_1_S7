public class FM3 implements Family {
int randomSave, ranNumRetrive;
	
	public void accept( Banking v ) {
		v.visit( this );
	}
	
	public int returnValue ( Banking v ) {
		return ranNumRetrive;
	}
	
	public int returnSValue( Banking v ) {
		return randomSave;
	}
	
	public String fm_store3() {
		randomSave = (int)(Math.random()*50);
		
		return "3 Storing			: +$" + randomSave;
	}

	public String fm_retrive3() {
		ranNumRetrive = (int)(Math.random()*80);
		return "3: Retriving		: -$" + ranNumRetrive;
	}

	public int returnValue() {
		return 0;
	}
	public int returnSValue() {
		return 0;
	}
}
