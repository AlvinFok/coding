import {Subrecipe} from './Subrecipe';
import {ProcessTool} from './ProcessTool';
import {ToolCommand} from './ToolCommand';

export interface Adapter {
	execute(sr: Subrecipe): void;
	addJobs(job: ToolCommand): void;
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
		
		public addJobs(job: ToolCommand): void
		{
				console.log('(Adapter A process subrecipe for Tool A)');
				console.log('(Adapter A add job to Tool A)');
				this.processTool_A.addJobs(job);
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
		
		public addJobs(job: ToolCommand): void
		{
				console.log('(Adapter B process subrecipe for Tool B)');
				console.log('(Adapter A add job to Tool A)');
				this.processTool_B.addJobs(job);
		}
}