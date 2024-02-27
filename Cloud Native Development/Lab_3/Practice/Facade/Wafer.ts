export class Wafer{
	public id: string;	
	public product: string;
	public genSubrecipeMode;
	
	constructor(id:string, product:string, genSubrecipeMode:string){
			this.id = id;			
			this.product = product;
			this.genSubrecipeMode = genSubrecipeMode;
	}
}