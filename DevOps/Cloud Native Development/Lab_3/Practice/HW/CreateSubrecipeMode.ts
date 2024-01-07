import {Wafer} from './Wafer';
import {Subrecipe} from './Subrecipe';
import {ProductStrategy} from './ProductStrategy';
import {MPStrategy} from './ProductStrategy';
import {PCStrategy} from './ProductStrategy';
import {NBStrategy} from './ProductStrategy';
import { N3Strategy, N5Strategy, N7Strategy, TeachStrategy } from './TeachStrategy';

export interface CreateSubrecipeMode{
		genSubrecipe(wafer: Wafer): Subrecipe;
}

export class ByProductStrategyMode implements CreateSubrecipeMode{
		public productStrategy : ProductStrategy;
		public teachStrategy : TeachStrategy;
		
		private decideProductStrategy(wafer: Wafer): ProductStrategy
		{
				if(wafer.product == 'Mobile Phone'){
						return new MPStrategy();
				}else if(wafer.product == 'Personal Computer'){
						return new PCStrategy();
				}else{
						return new NBStrategy();
				}					
		}
		
		private decideTeachStrategy(wafer:Wafer): TeachStrategy
		{
			if(wafer.teach == "N7"){
				return new N7Strategy();
			}
			else if(wafer.teach == "N5"){
				return new N5Strategy();
			}
			else{
				return new N3Strategy();
			}
		}
		
		public genSubrecipe(wafer: Wafer): Subrecipe
		{
				this.productStrategy = this.decideProductStrategy(wafer);				
				var type:string = this.productStrategy.genType()

				this.teachStrategy = this.decideTeachStrategy(wafer);
				var teach:string = this.teachStrategy.genTeach();

				return new Subrecipe('APC Subrecipe for[' + wafer.id + ']: A+B*(Fn of ' + type + ')' +' + (Fn of '+ teach +')');

		}					
}

export class RecommendMode implements CreateSubrecipeMode{				
		public genSubrecipe(wafer: Wafer): Subrecipe
		{
				return new Subrecipe('Recommend Subrecipe for[' + wafer.id + ']');	
		}
}

export class FeedforwardMode implements CreateSubrecipeMode{				
		public genSubrecipe(wafer: Wafer): Subrecipe
		{
				return new Subrecipe('Feedforward Subrecipe for[' + wafer.id + ']');
		}
}