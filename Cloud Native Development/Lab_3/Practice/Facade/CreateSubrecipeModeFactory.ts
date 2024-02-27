import {Wafer} from './Wafer';
import {Subrecipe} from './Subrecipe';
import {CreateSubrecipeMode} from './CreateSubrecipeMode';
import {ByProductStrategyMode} from './CreateSubrecipeMode';
import {RecommendMode} from './CreateSubrecipeMode';
import {FeedforwardMode} from './CreateSubrecipeMode';

export interface CreateSubrecipeModeFactory {
		genCreateMode(): CreateSubrecipeMode;	
}

export class ByProductStrategyFactory implements CreateSubrecipeModeFactory{
		public genCreateMode(): CreateSubrecipeMode{
				return new ByProductStrategyMode();
		}			
}

export class ByRecommandFactory implements CreateSubrecipeModeFactory{
		public genCreateMode(): CreateSubrecipeMode{
				return new RecommendMode();
		}				
}

export class ByFeedforwardFactory implements CreateSubrecipeModeFactory{
		public genCreateMode(): CreateSubrecipeMode{
				return new FeedforwardMode();
		}				
}