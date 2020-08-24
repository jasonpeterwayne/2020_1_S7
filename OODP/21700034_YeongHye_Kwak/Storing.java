class Storing implements Banking{
	public void visit( FM1 e ) {
		System.out.println( "Family Member " + e.fm_store1() );
	}
	public int reValue( FM1 e ) {
		return e.returnValue();
	}
	public int reSValue( FM1 e ) {
		return e.returnSValue();
	}
	
	public void visit( FM2 e ) {
		System.out.println( "Family Member " + e.fm_store2() );
	}
	public int reValue( FM2 e ) {
		return e.returnValue();
	}
	public int reSValue( FM2 e ) {
		return e.returnSValue();
	}
	
	public void visit( FM3 e ) {
		System.out.println( "Family Member " + e.fm_store3() );
	}
	public int reValue( FM3 e ) {
		return e.returnValue();
	}
	public int reSValue( FM3 e ) {
		return e.returnSValue();
	}
	
	public void visit( FM4 e ) {
		System.out.println( "Family Member " + e.fm_store4() );
	}
	public int reValue( FM4 e ) {
		return e.returnValue();
	}
	public int reSValue( FM4 e ) {
		return e.returnSValue();
	}
	
	public void visit( FM5 e ) {
		System.out.println( "Family Member " + e.fm_store5() );
	}
	public int reValue( FM5 e ) {
		return e.returnSValue();
	}
	public int reSValue( FM5 e ) {
		return e.returnValue();
	}
	
	public void visit( FM6 e ) {
		System.out.println( "Family Member " + e.fm_store6() );
	}	
	public int reValue( FM6 e ) {
		return e.returnValue();
	}
	public int reSValue( FM6 e ) {
		return e.returnSValue();
	}
}
