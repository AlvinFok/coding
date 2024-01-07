import {Strategy} from './Strategy';

export class Context{
		private strategy: Strategy;
		
		public setStrategy(strategy: Strategy): void
		{
				this.strategy = strategy;
		}
		
		public doSomething(data: string): void
		{
				this.strategy.execute(data);
		}
}