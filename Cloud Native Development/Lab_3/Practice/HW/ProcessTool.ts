import {Subrecipe} from './Subrecipe';
import {ToolCommand} from './ToolCommand';

export class ProcessTool{		
		public toolName: string;
		public jobs: Array<ToolCommand>;
		
		constructor(toolName: string){				
				this.toolName = toolName;
				this.jobs = new Array<ToolCommand>();
		}				
		
		public addJobs(job: ToolCommand): void
		{
				this.jobs.push(job);
		}				
		
		public execute(sr: Subrecipe): void
		{
				console.log('Process Tool '+ this.toolName +' execute subrecipe[ '+ sr.name +' ]');				
		};
		
		public executeCommand(): void
		{
				console.log('Tool[', this.toolName, '] start to execute jobs.');
				this.jobs.forEach(function(job){
						job.execute();
				})			
		};
}