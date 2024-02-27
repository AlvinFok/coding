export class Wafer{
	public id: string;	
	public product: string;
	public genSubrecipeMode;
	public teach:string;
	
	constructor(id:string, product:string, genSubrecipeMode:string, teach:string){
			this.id = id;			
			this.product = product;
			this.genSubrecipeMode = genSubrecipeMode;
			this.teach = teach;
	}
}