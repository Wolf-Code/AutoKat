export interface View<TArgs = any>
{
	preRender?: any
	render: (args?: TArgs) => string
	postRender?: any
	cleanup?: any
}