public class FM6 implements Family {
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
	
	public String fm_store6() {
		randomSave = (int)(Math.random()*50);
		return "6 Storing			: +$" + randomSave;
	}

	public String fm_retrive6() {
		ranNumRetrive = (int)(Math.random()*80);
		return "6: Retriving		: -$" + ranNumRetrive;
	}

	public int returnValue() {
		return 0;
	}
	public int returnSValue() {
		return 0;
	}
}
