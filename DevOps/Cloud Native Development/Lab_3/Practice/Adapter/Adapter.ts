import {Subrecipe} from './Subrecipe';
import {ProcessTool} from './ProcessTool';


export interface Adapter {
	execute(sr: Subrecipe): void
}

export class Adapter_A implements Adapter{
		public processTool_A: ProcessTool;
		
		constructor(processTool: ProcessTool){
				this.processTool_A = processTool;
		}
		
		public execute(sr: Subrecipe): void
		{
				console.log('(Adapter A process subrecipe for Tool A)');
				this.processTool_A.execute(sr);
		}
}

export class Adapter_B implements Adapter{
		public processTool_B: ProcessTool;
		
		constructor(processTool: ProcessTool){
				this.processTool_B = processTool;
		}
		
		public execute(sr: Subrecipe): void
		{
				console.log('(Adapter B process subrecipe for Tool B)');
				this.processTool_B.execute(sr);
		}
}

export class Adapter_C implements Adapter{
	public processTool_C: ProcessTool;
	
	constructor(processTool: ProcessTool){
			this.processTool_C = processTool;
	}
	
	public execute(sr: Subrecipe): void
	{
			console.log('(Adapter C process subrecipe for Tool C)');
			this.processTool_C.execute(sr);
	}
}