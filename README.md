# CastleDB-cpp-parser

_Quickly parse your CastleDB for use in your C++ codebase. It supports hot reload!_
<img src="media/Code_vr3EVVBErD.gif">

## Usage

Include the files located in the **.src/** folder in your codebase, then instantiate the CastleDBConverter class constructor to retrieve the data.

```
CastleDBConverter converter("res/helloworld.json");
```

Then extract your data, a nice feature is that you can grab only the fields you need.

```
                                //sheet name   //fields
data_db = converter.extract_data("HelloWorld", {"Name", "X", "Y", "Char"});
```

Use the update method to check for updates in the file for hot reload support
```
if(converter.update("res/helloworld.json")){
    //your code
}
```

## Thanks
Thanks for [ncannasse](https://github.com/ncannasse) for the creation of [CastleDB](https://github.com/ncannasse/castle) and to [nlohmann](https://github.com/nlohmann) for [json parser](https://github.com/nlohmann/json)
