import {Wafer} from './Wafer';
import {Subrecipe} from './Subrecipe';
import {ProductStrategy} from './ProductStrategy';
import {MPStrategy} from './ProductStrategy';
import {PCStrategy} from './ProductStrategy';
import {NBStrategy} from './ProductStrategy';

export interface CreateSubrecipeMode{
		genSubrecipe(wafer: Wafer): Subrecipe;
}

export class ByProductStrategyMode implements CreateSubrecipeMode{
		public productStrategy : ProductStrategy;
		
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
		
		public genSubrecipe(wafer: Wafer): Subrecipe
		{
				this.productStrategy = this.decideProductStrategy(wafer);				
				return this.productStrategy.genSubrecipe(wafer);
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