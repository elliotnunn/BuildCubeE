mk_output_d = :
ProjNm = AutoQuit

mk_source_d = {mk_output_d}
mk_obj_d = {mk_output_d}
mk_built_program = {mk_output_d}{ProjNm}

mk_CallC = SC
mk_COptions = -proto strict -w 17 -align mac68k -b -mbg off -opt space
mk_CallA = Asm
mk_AOptions = -case on


TheApplication ƒ "{mk_built_program}"

"{mk_obj_d}{ProjNm}.c.o" ƒ "{mk_source_d}{ProjNm}.c"
	{mk_CallC} "{mk_source_d}{ProjNm}.c" -o "{mk_obj_d}{ProjNm}.c.o" {mk_COptions}
"{mk_obj_d}{ProjNm}.a.o" ƒ "{mk_source_d}{ProjNm}.a"
	{mk_CallA} "{mk_source_d}{ProjNm}.a" -o "{mk_obj_d}{ProjNm}.a.o" {mk_AOptions}

ObjFiles = ∂
	"{mk_obj_d}{ProjNm}.a.o" ∂
	"{mk_obj_d}{ProjNm}.c.o" ∂


"{mk_obj_d}{ProjNm}.rsrc" ƒ "{mk_source_d}{ProjNm}.r"
	Rez -t rsrc -c RSED -i "{RIncludes}" "{mk_source_d}{ProjNm}.r" -o "{mk_obj_d}{ProjNm}.rsrc"

"{mk_built_program}" ƒ {ObjFiles} "{mk_obj_d}{ProjNm}.rsrc"
	Duplicate -y "{mk_obj_d}{ProjNm}.rsrc" "{mk_built_program}"
	Link -t FNDR -c MACS -rn ∂
		-sg Main=STDCLIB,SANELIB,CSANELib,SADEV,STDIO ∂
		-o {mk_built_program} ∂
		{ObjFiles} ∂
		"{Libraries}"Interface.o
	SetFile -d . -m . -a B "{mk_built_program}"
