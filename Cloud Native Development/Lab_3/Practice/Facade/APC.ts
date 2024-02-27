import {Wafer} from './Wafer';
import {Subrecipe} from './Subrecipe';
import {ProcessTool} from './ProcessTool';
import {Adapter} from './Adapter';
import {Adapter_A} from './Adapter';
import {Adapter_B} from './Adapter';
import {CreateSubrecipeModeFactory} from './CreateSubrecipeModeFactory';
import {ByProductStrategyFactory} from './CreateSubrecipeModeFactory';
import {ByRecommandFactory} from './CreateSubrecipeModeFactory';
import {ByFeedforwardFactory} from './CreateSubrecipeModeFactory';

export class APC{
		
		public adapter: Adapter;
		public subrecipeFactory: CreateSubrecipeModeFactory;
		
		public execute(wafer: Wafer, processTool: ProcessTool): void
		{				
				var sr = this.genSubrecipeForProd(wafer);
				
				if(processTool.toolName == 'A'){
						this.adapter = new Adapter_A(processTool);
				}else if(processTool.toolName == 'B'){
						this.adapter = new Adapter_B(processTool);
				}else{
						// default tool A
						this.adapter = new Adapter_A(processTool);
				}
				
				this.adapter.execute(sr);
		}
		
		public genSubrecipeForProd(wafer: Wafer): Subrecipe
		{
				console.log('Gen subrecipe for production.');
				var subrecipe = this.genSubrecipe(wafer);
				this.checkSubrecipeSpec(subrecipe);
				this.log(subrecipe);
				this.updateAPCModel(subrecipe);
				
				return subrecipe;			
		}
		
		public preview(wafer: Wafer, processTool: ProcessTool): Subrecipe
		{
				console.log('Preview APC Subrecipe.');
				var subrecipe = this.genSubrecipe(wafer);
				this.checkSubrecipeSpec(subrecipe);				
				
				return subrecipe;		
		}
		
		private genSubrecipe(wafer: Wafer): Subrecipe
		{
				if(wafer.genSubrecipeMode == 'ByProductStrategy'){
						this.subrecipeFactory = new ByProductStrategyFactory();
				}else if(wafer.genSubrecipeMode == 'Recommend'){
						this.subrecipeFactory = new ByRecommandFactory();
				}else{
						this.subrecipeFactory = new ByFeedforwardFactory();
				}
				
				return this.subrecipeFactory.genCreateMode().genSubrecipe(wafer);	
		}			

		private checkSubrecipeSpec(subrecipe: Subrecipe): void{
				console.log('--> check subrecipe spec for ' + subrecipe.name);
		}
		
		private log(subrecipe: Subrecipe): void{
				console.log('--> log subrecipe for ' + subrecipe.name);
		}
		
		private updateAPCModel(subrecipe: Subrecipe): void{
				console.log('--> update APC model for ' + subrecipe.name);
		}		
}