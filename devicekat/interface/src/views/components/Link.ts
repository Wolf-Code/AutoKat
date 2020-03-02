import { View } from "../../router/View";

export interface LinkArgs
{
	label: string,
	route: string
}

export const Link : View<LinkArgs> = {
	render: args => `<a href="#${args.route}">${args.label}</a>`
}