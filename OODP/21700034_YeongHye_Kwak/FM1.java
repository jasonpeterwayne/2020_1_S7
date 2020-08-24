public class FM1 implements Family {
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
	
	public String fm_store1() {
		randomSave = (int)(Math.random()*50);
		
		return "1 Storing			: +$" + randomSave;
	}

	public String fm_retrive1() {
		ranNumRetrive = (int)(Math.random()*80);
		return "1: Retriving		: -$" + ranNumRetrive;
	}

	public int returnValue() {
		return 0;
	}
	public int returnSValue() {
		return 0;
	}
}
