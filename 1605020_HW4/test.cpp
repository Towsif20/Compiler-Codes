start : program {	}

	  ;

program : program unit {$<symbolinfo>$=new SymbolInfo(); fprintf(parsertext,"Line at %d : program->program unit\n\n",line_count);
						fprintf(parsertext,"%s %s\n\n",$<symbolinfo>1->get_name().c_str(),$<symbolinfo>2->get_name().c_str()); 
						$<symbolinfo>$->set_name($<symbolinfo>1->get_name()+$<symbolinfo>2->get_name());
						}

	| unit {$<symbolinfo>$=new SymbolInfo(); fprintf(parsertext,"Line at %d : program->unit\n\n",line_count);
	fprintf(parsertext,"%s\n\n",$<symbolinfo>1->get_name().c_str());
	$<symbolinfo>$->set_name($<symbolinfo>1->get_name());
	}
	;

unit : var_declaration {$<symbolinfo>$=new SymbolInfo(); fprintf(parsertext,"Line at %d : unit->var_declaration\n\n",line_count);
						fprintf(parsertext,"%s\n\n",$<symbolinfo>1->get_name().c_str()); 
						$<symbolinfo>$->set_name($<symbolinfo>1->get_name()+"\n");}
     | func_declaration {$<symbolinfo>$=new SymbolInfo(); fprintf(parsertext,"Line at %d : unit->func_declaration\n\n",line_count);
	 					fprintf(parsertext,"%s\n\n",$<symbolinfo>1->get_name().c_str()); 
						 $<symbolinfo>$->set_name($<symbolinfo>1->get_name()+"\n");
						}
     | func_definition { $<symbolinfo>$=new SymbolInfo(); fprintf(parsertext,"Line at %d : unit->func_definition\n\n",line_count);
	 					 fprintf(parsertext,"%s\n\n",$<symbolinfo>1->get_name().c_str());
						 $<symbolinfo>$->set_name($<symbolinfo>1->get_name()+"\n");
						 }
     ;

func_declaration : type_specifier ID  LPAREN  parameter_list RPAREN SEMICOLON {$<symbolinfo>$=new SymbolInfo(); fprintf(parsertext,"Line at %d : func_declaration->type_specifier ID LPAREN parameter_list RPAREN SEMICOLON\n\n",line_count);
		fprintf(parsertext,"%s %s(%s);\n\n",$<symbolinfo>1->get_name().c_str(),$<symbolinfo>2->get_name().c_str(),$<symbolinfo>4->get_name().c_str());
		SymbolInfo *s=table->lookup($<symbolinfo>2->get_name());
				if(s==0){
					table->Insert($<symbolinfo>2->get_name(),"ID","Function");
					s=table->lookup($<symbolinfo>2->get_name());
					s->set_isFunction();
					for(int i=0;i<para_list.size();i++){
						s->get_isFunction()->add_number_of_parameter(para_list[i]->get_name(),para_list[i]->get_dectype());
					//cout<<para_list[i]->get_dectype()<<endl;
					}
					para_list.clear();s->get_isFunction()->set_return_type($<symbolinfo>1->get_name());
				} 
				else{
					int num=s->get_isFunction()->get_number_of_parameter();
				//	cout<<line_count<<" "<<para_list.size()<<endl;
				//	$<symbolinfo>$->set_dectype(s->get_isFunction()->get_return_type());
					if(num!=para_list.size()){
						error_count++;
						fprintf(error,"Error at Line No.%d:  Invalid number of parameters \n\n",line_count);

					} else{
					
					vector<string>para_type=s->get_isFunction()->get_paratype();
					for(int i=0;i<para_list.size();i++){
					if(para_list[i]->get_dectype()!=para_type[i]){
								error_count++;
								fprintf(error,"Error at Line No.%d: Type Mismatch \n\n",line_count);
								break;
							}
						}
						if(s->get_isFunction()->get_return_type()!=$<symbolinfo>1->get_name()){
								error_count++;
								fprintf(error,"Error at Line No.%d: Return Type Mismatch \n\n",line_count);
						}
						para_list.clear();
					}
					
				}
				
		$<symbolinfo>$->set_name($<symbolinfo>1->get_name()+" "+$<symbolinfo>2->get_name()+"("+$<symbolinfo>4->get_name()+");");
		}
		|type_specifier ID LPAREN RPAREN SEMICOLON {$<symbolinfo>$=new SymbolInfo(); fprintf(parsertext,"Line at %d : func_declaration->type_specifier ID LPAREN RPAREN SEMICOLON\n\n",line_count);
				fprintf(parsertext,"%s %s();\n\n",$<symbolinfo>1->get_name().c_str(),$<symbolinfo>2->get_name().c_str());
				SymbolInfo *s=table->lookup($<symbolinfo>2->get_name());
				if(s==0){
					table->Insert($<symbolinfo>2->get_name(),"ID","Function");
					s=table->lookup($<symbolinfo>2->get_name());
					s->set_isFunction();s->get_isFunction()->set_return_type($<symbolinfo>1->get_name());
				}
				else{
					if(s->get_isFunction()->get_number_of_parameter()!=0){
						error_count++;
						fprintf(error,"Error at Line No.%d:  Invalid number of parameters \n\n",line_count);
					}
					if(s->get_isFunction()->get_return_type()!=$<symbolinfo>1->get_name()){
						error_count++;
						fprintf(error,"Error at Line No.%d: Return Type Mismatch \n\n",line_count);
					}

				}
				$<symbolinfo>$->set_name($<symbolinfo>1->get_name()+" "+$<symbolinfo>2->get_name()+"();");
		}
		;

func_definition : type_specifier ID  LPAREN  parameter_list RPAREN {$<symbolinfo>$=new SymbolInfo(); 

				SymbolInfo *s=table->lookup($<symbolinfo>2->get_name()); 
				if(s!=0){ 
					if(s->get_isFunction()->get_isdefined()==0){
					int num=s->get_isFunction()->get_number_of_parameter();
				//	cout<<line_count<<" "<<para_list.size()<<endl;
				//	$<symbolinfo>$->set_dectype(s->get_isFunction()->get_return_type());
					if(num!=para_list.size()){
						error_count++;
						fprintf(error,"Error at Line No.%d:  Invalid number of parameters \n\n",line_count);

					} else{
					
					vector<string>para_type=s->get_isFunction()->get_paratype();
					for(int i=0;i<para_list.size();i++){
					if(para_list[i]->get_dectype()!=para_type[i]){
								error_count++;
								fprintf(error,"Error at Line No.%d: Type Mismatch \n\n",line_count);
								break;
							}
						}
						if(s->get_isFunction()->get_return_type()!=$<symbolinfo>1->get_name()){
								error_count++;
								fprintf(error,"Error at Line No.%d: Return Type Mismatch1 \n\n",line_count);
						}
					//	para_list.clear();
					}
					s->get_isFunction()->set_isdefined();}
					else{
						error_count++;
						fprintf(error,"Error at Line No.%d:  Multiple defination of function %s\n\n",line_count,$<symbolinfo>2->get_name().c_str());
											
					}
				}
				else{ //cout<<para_list.size()<<" "<<line_count<<endl;
						table->Insert($<symbolinfo>2->get_name(),"ID","Function");
						s=table->lookup($<symbolinfo>2->get_name());
						s->set_isFunction();
						//cout<<s->get_isFunction()->get_number_of_parameter()<<endl;
						s->get_isFunction()->set_isdefined();
						for(int i=0;i<para_list.size();i++){
							s->get_isFunction()->add_number_of_parameter(para_list[i]->get_name(),para_list[i]->get_dectype());
					//	cout<<para_list[i]->get_dectype()<<para_list[i]->get_name()<<endl;
					}
				//	para_list.clear();
					s->get_isFunction()->set_return_type($<symbolinfo>1->get_name());
					//cout<<line_count<<" "<<s->get_isFunction()->get_return_type()<<endl;
				}

				} compound_statement 
				{fprintf(parsertext,"Line at %d : func_definition->type_specifier ID LPAREN parameter_list RPAREN compound_statement \n\n",line_count);
				fprintf(parsertext,"%s %s(%s) %s \n\n",$<symbolinfo>1->get_name().c_str(),$<symbolinfo>2->get_name().c_str(),$<symbolinfo>4->get_name().c_str(),$<symbolinfo>7->get_name().c_str());
				
			
				$<symbolinfo>$->set_name($<symbolinfo>1->get_name()+" "+$<symbolinfo>2->get_name()+"("+$<symbolinfo>4->get_name()+")"+$<symbolinfo>7->get_name());
				}
		| type_specifier ID LPAREN RPAREN { $<symbolinfo>$=new SymbolInfo(); SymbolInfo *s=table->lookup($<symbolinfo>2->get_name());
											if(s==0){
												table->Insert($<symbolinfo>2->get_name(),"ID","Function");
												s=table->lookup($<symbolinfo>2->get_name());
												s->set_isFunction();
												s->get_isFunction()->set_isdefined();
												s->get_isFunction()->set_return_type($<symbolinfo>1->get_name());
										//	cout<<line_count<<" "<<s->get_isFunction()->get_return_type()<<endl;
											}
											else if(s->get_isFunction()->get_isdefined()==0){
												if(s->get_isFunction()->get_number_of_parameter()!=0){
													error_count++;
													fprintf(error,"Error at Line No.%d:  Invalid number of parameters \n\n",line_count);
												}
												if(s->get_isFunction()->get_return_type()!=$<symbolinfo>1->get_name()){
													error_count++;
													fprintf(error,"Error at Line No.%d: Return Type Mismatch \n\n",line_count);
												}

												s->get_isFunction()->set_isdefined();
											}
											else{
												error_count++;
												fprintf(error,"Error at Line No.%d:  Multiple defination of function %s\n\n",line_count,$<symbolinfo>2->get_name().c_str());
											}
											
											$<symbolinfo>1->set_name($<symbolinfo>1->get_name()+" "+$<symbolinfo>2->get_name()+"()");
											} compound_statement {
											fprintf(parsertext,"Line at %d : func_definition->type_specifier ID LPAREN RPAREN compound_statement\n\n",line_count);
											fprintf(parsertext,"%s %s\n\n",$<symbolinfo>1->get_name().c_str(),$<symbolinfo>6->get_name().c_str());
											$<symbolinfo>$->set_name($<symbolinfo>1->get_name()+$<symbolinfo>6->get_name());
			
					}
 		;


parameter_list  : parameter_list COMMA type_specifier ID {$<symbolinfo>$=new SymbolInfo(); fprintf(parsertext,"Line at %d : parameter_list->parameter_list COMMA type_specifier ID\n\n",line_count);
															fprintf(parsertext,"%s,%s %s\n\n",$<symbolinfo>1->get_name().c_str(),$<symbolinfo>3->get_name().c_str(),$<symbolinfo>4->get_name().c_str());
															 para_list.push_back(new SymbolInfo($<symbolinfo>4->get_name(),"ID",$<symbolinfo>3->get_name()));
															$<symbolinfo>$->set_name($<symbolinfo>1->get_name()+","+$<symbolinfo>3->get_name()+" "+$<symbolinfo>4->get_name());
															}
		| parameter_list COMMA type_specifier {$<symbolinfo>$=new SymbolInfo(); fprintf(parsertext,"Line at %d : parameter_list->parameter_list COMMA type_specifier\n\n",line_count);
											fprintf(parsertext,"%s,%s\n\n",$<symbolinfo>1->get_name().c_str(),$<symbolinfo>3->get_name().c_str());
											para_list.push_back(new SymbolInfo("","ID",$<symbolinfo>3->get_name()));
											$<symbolinfo>$->set_name($<symbolinfo>1->get_name()+","+$<symbolinfo>3->get_name());

											}
 		| type_specifier ID {$<symbolinfo>$=new SymbolInfo(); fprintf(parsertext,"Line at %d : parameter_list->type_specifier ID\n\n",line_count);
		 					fprintf(parsertext,"%s %s\n\n",$<symbolinfo>1->get_name().c_str(),$<symbolinfo>2->get_name().c_str());
							para_list.push_back(new SymbolInfo($<symbolinfo>2->get_name(),"ID",$<symbolinfo>1->get_name()));
		 					$<symbolinfo>$->set_name($<symbolinfo>1->get_name()+" "+$<symbolinfo>2->get_name());
							}
		| type_specifier {$<symbolinfo>$=new SymbolInfo(); fprintf(parsertext,"Line at %d : parameter_list->type_specifier\n\n",line_count);
			fprintf(parsertext,"%s \n\n",$<symbolinfo>1->get_name().c_str());
			para_list.push_back(new SymbolInfo("","ID",$<symbolinfo>1->get_name()));
			$<symbolinfo>$->set_name($<symbolinfo>1->get_name()+" ");
		}
 		;


compound_statement : LCURL {table->Enter_Scope();
		//	cout<<line_count<<" "<<para_list.size()<<endl;
			for(int i=0;i<para_list.size();i++)
				table->Insert(para_list[i]->get_name(),"ID",para_list[i]->get_dectype());
				//table->printcurrent();
				para_list.clear();
			} statements RCURL {$<symbolinfo>$=new SymbolInfo(); fprintf(parsertext,"Line at %d : compound_statement->LCURL statements RCURL\n\n",line_count);
											fprintf(parsertext,"{%s}\n\n",$<symbolinfo>3->get_name().c_str());
											$<symbolinfo>$->set_name("{\n"+$<symbolinfo>3->get_name()+"\n}");
											table->printall();
											table->Exit_Scope();
											}
 		    | LCURL RCURL {table->Enter_Scope();
				 for(int i=0;i<para_list.size();i++)
				table->Insert(para_list[i]->get_name(),"ID",para_list[i]->get_dectype());
				//table->printcurrent();
				para_list.clear();
				$<symbolinfo>$=new SymbolInfo(); fprintf(parsertext,"Line at %d : compound_statement->LCURL RCURL\n\n",line_count);
			 				fprintf(parsertext,"{}\n\n");
			 				$<symbolinfo>$->set_name("{}");
							table->printall();
							table->Exit_Scope();
			 }
 		    ;

var_declaration : type_specifier declaration_list SEMICOLON {$<symbolinfo>$=new SymbolInfo(); fprintf(parsertext,"Line at %d : var_declaration->type_specifier declaration_list SEMICOLON\n\n",line_count);
															fprintf(parsertext,"%s %s;\n\n",$<symbolinfo>1->get_name().c_str(),$<symbolinfo>2->get_name().c_str());
															if($<symbolinfo>1->get_name()=="void "){
																error_count++;
																fprintf(error,"Error at Line No.%d: TYpe specifier can not be void \n\n",line_count);
																	
															}
															else{
															for(int i=0;i<dec_list.size();i++){
																if(table->lookupcurrent(dec_list[i]->get_name())){
																	error_count++;
																	fprintf(error,"Error at Line No.%d:  Multiple Declaration of %s \n\n",line_count,dec_list[i]->get_name().c_str());
																	continue;
																}
																if(dec_list[i]->get_type().size()==3){
																	dec_list[i]->set_type(dec_list[i]->get_type().substr(0,dec_list[i]->get_type().size () - 1));
																	table->Insert(dec_list[i]->get_name(),dec_list[i]->get_type(),$<symbolinfo>1->get_name()+"array");
																}else
																table->Insert(dec_list[i]->get_name(),dec_list[i]->get_type(),$<symbolinfo>1->get_name());
															}}
															dec_list.clear();
															$<symbolinfo>$->set_name($<symbolinfo>1->get_name()+" "+$<symbolinfo>2->get_name()+";");
															}
 		 ;

type_specifier	: INT  {$<symbolinfo>$=new SymbolInfo(); fprintf(parsertext,"Line at %d : type_specifier	: INT\n\n",line_count);fprintf(parsertext,"int \n\n");
				$<symbolinfo>$->set_name("int ");
				}
 		| FLOAT  {$<symbolinfo>$=new SymbolInfo(); fprintf(parsertext,"Line at %d : type_specifier	: FLOAT\n\n",line_count);fprintf(parsertext,"float \n\n");
		 $<symbolinfo>$->set_name("float ");
		 }
 		| VOID  {$<symbolinfo>$=new SymbolInfo(); fprintf(parsertext,"Line at %d : type_specifier	: VOID\n\n",line_count);fprintf(parsertext,"void \n\n");
		 $<symbolinfo>$->set_name("void ");
		 }
 		;

declaration_list : declaration_list COMMA ID {$<symbolinfo>$=new SymbolInfo(); fprintf(parsertext,"Line at %d : declaration_list->declaration_list COMMA ID\n\n",line_count);
											fprintf(parsertext,"%s,%s\n\n",$<symbolinfo>1->get_name().c_str(),$<symbolinfo>3->get_name().c_str());
												dec_list.push_back(new SymbolInfo($<symbolinfo>3->get_name(),"ID"));
											$<symbolinfo>$->set_name($<symbolinfo>1->get_name()+","+$<symbolinfo>3->get_name());
											}
 		  | declaration_list COMMA ID LTHIRD CONST_INT RTHIRD {$<symbolinfo>$=new SymbolInfo(); fprintf(parsertext,"Line at %d : declaration_list->declaration_list COMMA ID LTHIRD CONST_INT RTHIRD\n\n",line_count);
		   														fprintf(parsertext,"%s,%s[%s]\n\n",$<symbolinfo>1->get_name().c_str(),$<symbolinfo>3->get_name().c_str(),$<symbolinfo>5->get_name().c_str());
																dec_list.push_back(new SymbolInfo($<symbolinfo>3->get_name(),"IDa"));
																$<symbolinfo>$->set_name($<symbolinfo>1->get_name()+","+$<symbolinfo>3->get_name()+"["+$<symbolinfo>5->get_name()+"]");
																   }
 		  | ID {$<symbolinfo>$=new SymbolInfo(); fprintf(parsertext,"Line at %d : declaration_list->ID\n\n",line_count);
		   fprintf(parsertext,"%s\n\n",$<symbolinfo>1->get_name().c_str());
		   	dec_list.push_back(new SymbolInfo($<symbolinfo>1->get_name(),"ID"));
			$<symbolinfo>$->set_name($<symbolinfo>1->get_name());
		
		   }
 		  | ID LTHIRD CONST_INT RTHIRD {$<symbolinfo>$=new SymbolInfo(); fprintf(parsertext,"Line at %d : declaration_list->ID LTHIRD CONST_INT RTHIRD\n\n",line_count);
		   fprintf(parsertext,"%s[%s]\n\n",$<symbolinfo>1->get_name().c_str(),$<symbolinfo>3->get_name().c_str());
		   	dec_list.push_back(new SymbolInfo($<symbolinfo>1->get_name(),"IDa"));
		   	$<symbolinfo>$->set_name($<symbolinfo>1->get_name()+"["+$<symbolinfo>3->get_name()+"]");

		   }
 		  ;

statements : statement {$<symbolinfo>$=new SymbolInfo(); fprintf(parsertext,"Line at %d : statements->statement\n\n",line_count);
						fprintf(parsertext,"%s\n\n",$<symbolinfo>1->get_name().c_str()); 
						$<symbolinfo>$->set_name($<symbolinfo>1->get_name());
						}
	   | statements statement {$<symbolinfo>$=new SymbolInfo(); fprintf(parsertext,"Line at %d : statements->statements statement\n\n",line_count);
	   						fprintf(parsertext,"%s %s\n\n",$<symbolinfo>1->get_name().c_str(),$<symbolinfo>2->get_name().c_str()); 
							   $<symbolinfo>$->set_name($<symbolinfo>1->get_name()+"\n"+$<symbolinfo>2->get_name()); 
							   }
	   ;

statement : var_declaration { $<symbolinfo>$=new SymbolInfo();fprintf(parsertext,"Line at %d : statement -> var_declaration\n\n",line_count);
							fprintf(parsertext,"%s\n\n",$<symbolinfo>1->get_name().c_str());
							$<symbolinfo>$->set_name($<symbolinfo>1->get_name()); 

							}
	  | expression_statement {$<symbolinfo>$=new SymbolInfo();fprintf(parsertext,"Line at %d : statement -> expression_statement\n\n",line_count);
	  						fprintf(parsertext,"%s\n\n",$<symbolinfo>1->get_name().c_str()); 
							$<symbolinfo>$->set_name($<symbolinfo>1->get_name()); 

							  }
	  | compound_statement {$<symbolinfo>$=new SymbolInfo();fprintf(parsertext,"Line at %d : statement->compound_statement\n\n",line_count);
	  						fprintf(parsertext,"%s\n\n",$<symbolinfo>1->get_name().c_str()); 
							 $<symbolinfo>$->set_name($<symbolinfo>1->get_name()); 
 
							  }
	  | FOR LPAREN expression_statement expression_statement expression RPAREN statement {$<symbolinfo>$=new SymbolInfo();fprintf(parsertext,"Line at %d : statement ->FOR LPAREN expression_statement expression_statement expression RPAREN statement\n\n",line_count);
	  																					fprintf(parsertext,"for(%s %s %s)\n%s \n\n",$<symbolinfo>3->get_name().c_str(),$<symbolinfo>4->get_name().c_str(),$<symbolinfo>5->get_name().c_str(),$<symbolinfo>7->get_name().c_str());
																						if($<symbolinfo>3->get_dectype()=="void "){
																							error_count++;
																							fprintf(error,"Error at Line No.%d:  Type Mismatch \n\n",line_count);
																							//$<symbolinfo>$->set_dectype("int "); 
																						}
																						
																						$<symbolinfo>$->set_name("for("+$<symbolinfo>3->get_name()+$<symbolinfo>4->get_name()+$<symbolinfo>5->get_name()+")\n"+$<symbolinfo>5->get_name()); 

																						  }
	  | IF LPAREN expression RPAREN statement %prec LOWER_THAN_ELSE {$<symbolinfo>$=new SymbolInfo();fprintf(parsertext,"Line at %d : statement->IF LPAREN expression RPAREN statement\n\n",line_count);
	  																fprintf(parsertext,"if(%s)\n%s\n\n",$<symbolinfo>3->get_name().c_str(),$<symbolinfo>5->get_name().c_str());
																	if($<symbolinfo>3->get_dectype()=="void "){
																		error_count++;
																		fprintf(error,"Error at Line No.%d:  Type Mismatch \n\n",line_count);
																//$<symbolinfo>$->set_dectype("int "); 
																	}
																	
																	$<symbolinfo>$->set_name("if("+$<symbolinfo>3->get_name()+")\n"+$<symbolinfo>5->get_name()); 

																	  }
	  | IF LPAREN expression RPAREN statement ELSE statement {$<symbolinfo>$=new SymbolInfo();fprintf(parsertext,"Line at %d : statement->IF LPAREN expression RPAREN statement ELSE statement\n\n",line_count);
	  														fprintf(parsertext,"if(%s)\n%s\n else \n %s\n\n",$<symbolinfo>3->get_name().c_str(),$<symbolinfo>5->get_name().c_str(),$<symbolinfo>7->get_name().c_str());
															if($<symbolinfo>3->get_dectype()=="void "){
																error_count++;
																fprintf(error,"Error at Line No.%d:  Type Mismatch \n\n",line_count);
																//$<symbolinfo>$->set_dectype("int "); 
															}
															
															$<symbolinfo>$->set_name("if("+$<symbolinfo>3->get_name()+")\n"+$<symbolinfo>5->get_name()+" else \n"+$<symbolinfo>7->get_name()); 
															}

	  | WHILE LPAREN expression RPAREN statement {$<symbolinfo>$=new SymbolInfo();fprintf(parsertext,"Line at %d : statement->WHILE LPAREN expression RPAREN statement\n\n",line_count);
	  											fprintf(parsertext,"while(%s)\n%s\n\n",$<symbolinfo>3->get_name().c_str(),$<symbolinfo>5->get_name().c_str());
												  if($<symbolinfo>3->get_dectype()=="void "){
													error_count++;
													fprintf(error,"Error at Line No.%d:  Type Mismatch \n\n",line_count);
												//	$<symbolinfo>$->set_dectype("int "); 
												}
												  $<symbolinfo>$->set_name("while("+$<symbolinfo>3->get_name()+")\n"+$<symbolinfo>5->get_name()); 
												  }
	  | PRINTLN LPAREN ID RPAREN SEMICOLON {$<symbolinfo>$=new SymbolInfo();fprintf(parsertext,"Line at %d : statement->PRINTLN LPAREN ID RPAREN SEMICOLON\n\n",line_count);
	  										fprintf(parsertext,"\n (%s);\n\n",$<symbolinfo>3->get_name().c_str());
											  $<symbolinfo>$->set_name("\n("+$<symbolinfo>3->get_name()+")"); 
											  }
	  | RETURN expression SEMICOLON {$<symbolinfo>$=new SymbolInfo();fprintf(parsertext,"Line at %d : statement->RETURN expression SEMICOLON\n\n",line_count);
	  								fprintf(parsertext,"return %s;\n\n",$<symbolinfo>2->get_name().c_str());
									if($<symbolinfo>2->get_dectype()=="void "){
												error_count++;
												fprintf(error,"Error at Line No.%d:  Type Mismatch \n\n",line_count);
												$<symbolinfo>$->set_dectype("int "); 
									}
									$<symbolinfo>$->set_name("return "+$<symbolinfo>2->get_name()+";"); 
									}
	  ;

expression_statement 	: SEMICOLON	{$<symbolinfo>$=new SymbolInfo();fprintf(parsertext,"Line at %d : expression_statement->SEMICOLON\n\n",line_count);
									fprintf(parsertext,";\n\n"); 
									$<symbolinfo>$->set_name(";"); 
									}
			| expression SEMICOLON {$<symbolinfo>$=new SymbolInfo();fprintf(parsertext,"Line at %d : expression_statement->expression SEMICOLON\n\n",line_count);
									fprintf(parsertext,"%s;\n\n",$<symbolinfo>1->get_name().c_str());
									$<symbolinfo>$->set_name($<symbolinfo>1->get_name()+";"); 
									}
			;

variable : ID 		{$<symbolinfo>$=new SymbolInfo();
					fprintf(parsertext,"Line at %d : variable->ID\n\n",line_count);
					fprintf(parsertext,"%s\n\n",$<symbolinfo>1->get_name().c_str());
					if(table->lookup($<symbolinfo>1->get_name())==0){
						 error_count++;
						fprintf(error,"Error at Line No.%d:  Undeclared Variable: %s \n\n",line_count,$<symbolinfo>1->get_name().c_str());
					
					}
					else if(table->lookup($<symbolinfo>1->get_name())->get_dectype()=="int array" || table->lookup($<symbolinfo>1->get_name())->get_dectype()=="float array"){
						 error_count++;
						fprintf(error,"Error at Line No.%d:  Not an array: %s \n\n",line_count,$<symbolinfo>1->get_name().c_str());
					}
					if(table->lookup($<symbolinfo>1->get_name())!=0){
						//cout<<line_count<<" "<<$<symbolinfo>1->get_name()<<" "<<table->lookup($<symbolinfo>1->get_name())->get_dectype()<<endl;
						$<symbolinfo>$->set_dectype(table->lookup($<symbolinfo>1->get_name())->get_dectype()); 
					}
						$<symbolinfo>$->set_name($<symbolinfo>1->get_name()); 
						
						
					}
	 | ID LTHIRD expression RTHIRD  {$<symbolinfo>$=new SymbolInfo();fprintf(parsertext,"Line at %d : variable->ID LTHIRD expression RTHIRD\n\n",line_count);
	 								fprintf(parsertext,"%s[%s]\n\n",$<symbolinfo>1->get_name().c_str(),$<symbolinfo>3->get_name().c_str());
									if(table->lookup($<symbolinfo>1->get_name())==0){
										error_count++;
										fprintf(error,"Error at Line No.%d:  Undeclared Variable: %s \n\n",line_count,$<symbolinfo>1->get_name().c_str());
									}
									//cout<<line_count<<" "<<$<symbolinfo>3->get_dectype()<<endl;
									if($<symbolinfo>3->get_dectype()=="float "||$<symbolinfo>3->get_dectype()=="void "){
										 error_count++;
										fprintf(error,"Error at Line No.%d:  Non-integer Array Index  \n\n",line_count);
									}
									if(table->lookup($<symbolinfo>1->get_name())!=0){
										//cout<<line_count<<" "<<table->lookup($<symbolinfo>1->get_name())->get_dectype()<<endl;
										if(table->lookup($<symbolinfo>1->get_name())->get_dectype()!="int array" && table->lookup($<symbolinfo>1->get_name())->get_dectype()!="float array")
										{
									
											error_count++;
											fprintf(error,"Error at Line No.%d:  Type Mismatch \n\n",line_count);	
										}
										
										if(table->lookup($<symbolinfo>1->get_name())->get_dectype()=="int array"){

											$<symbolinfo>1->set_dectype("int ");
										}
										if(table->lookup($<symbolinfo>1->get_name())->get_dectype()=="float array"){
											$<symbolinfo>1->set_dectype("float ");
										}
										$<symbolinfo>$->set_dectype($<symbolinfo>1->get_dectype()); 
										
									}
									$<symbolinfo>$->set_name($<symbolinfo>1->get_name()+"["+$<symbolinfo>3->get_name()+"]");  
									
									}
	 ;
expression : logic_expression	{$<symbolinfo>$=new SymbolInfo();fprintf(parsertext,"Line at %d : expression->logic_expression\n\n",line_count);
 								fprintf(parsertext,"%s\n\n",$<symbolinfo>1->get_name().c_str());
								 	$<symbolinfo>$->set_name($<symbolinfo>1->get_name()); 
									$<symbolinfo>$->set_dectype($<symbolinfo>1->get_dectype()); 
								 }
	   | variable ASSIGNOP logic_expression {$<symbolinfo>$=new SymbolInfo();fprintf(parsertext,"Line at %d : expression->variable ASSIGNOP logic_expression\n\n",line_count);
	   										fprintf(parsertext,"%s=%s\n\n",$<symbolinfo>1->get_name().c_str(),$<symbolinfo>3->get_name().c_str());
											   if($<symbolinfo>3->get_dectype()=="void "){
												error_count++;
												fprintf(error,"Error at Line No.%d:  Type Mismatch \n\n",line_count);
												$<symbolinfo>$->set_dectype("int "); 
											}else if(table->lookup($<symbolinfo>1->get_name())!=0) {
												//cout<<line_count<<" "<<table->lookup($<symbolinfo>1->get_name())->get_dectype()<<""<<$<symbolinfo>3->get_dectype()<<endl;
												if(table->lookup($<symbolinfo>1->get_name())->get_dectype()!=$<symbolinfo>3->get_dectype()){
													 error_count++;
													fprintf(error,"Error at Line No.%d: Type Mismatch \n\n",line_count);
												}
											}
											$<symbolinfo>$->set_dectype($<symbolinfo>1->get_dectype()); 
											$<symbolinfo>$->set_name($<symbolinfo>1->get_name()+"="+$<symbolinfo>3->get_name());  

											}
	   ;
logic_expression : rel_expression 	{$<symbolinfo>$=new SymbolInfo();fprintf(parsertext,"Line at %d : logic_expression->rel_expression\n\n",line_count);
										fprintf(parsertext,"%s\n\n",$<symbolinfo>1->get_name().c_str());
										$<symbolinfo>$->set_name($<symbolinfo>1->get_name()); 
										$<symbolinfo>$->set_dectype($<symbolinfo>1->get_dectype()); 

										}
		 | rel_expression LOGICOP rel_expression {$<symbolinfo>$=new SymbolInfo();fprintf(parsertext,"Line at %d : logic_expression->rel_expression LOGICOP rel_expression\n\n",line_count);
		 											fprintf(parsertext,"%s%s%s\n\n",$<symbolinfo>1->get_name().c_str(),$<symbolinfo>2->get_name().c_str(),$<symbolinfo>3->get_name().c_str());
													 if($<symbolinfo>1->get_dectype()=="void "||$<symbolinfo>3->get_dectype()=="void "){
														error_count++;
														fprintf(error,"Error at Line No.%d:  Type Mismatch \n\n",line_count);
														$<symbolinfo>$->set_dectype("int "); 
													}
										 			$<symbolinfo>$->set_dectype("int "); 
		 											$<symbolinfo>$->set_name($<symbolinfo>1->get_name()+$<symbolinfo>2->get_name()+$<symbolinfo>3->get_name());  

												}
		 ;

rel_expression	: simple_expression {$<symbolinfo>$=new SymbolInfo();fprintf(parsertext,"Line at %d : rel_expression->simple_expression\n\n",line_count);
									fprintf(parsertext,"%s\n\n",$<symbolinfo>1->get_name().c_str());
									$<symbolinfo>$->set_name($<symbolinfo>1->get_name()); 
									 $<symbolinfo>$->set_dectype($<symbolinfo>1->get_dectype()); 
									 
									}
		| simple_expression RELOP simple_expression	 {$<symbolinfo>$=new SymbolInfo();fprintf(parsertext,"Line at %d : rel_expression->simple_expression RELOP simple_expression\n\n",line_count);
													fprintf(parsertext,"%s%s%s\n\n",$<symbolinfo>1->get_name().c_str(),$<symbolinfo>2->get_name().c_str(),$<symbolinfo>3->get_name().c_str());
													if($<symbolinfo>1->get_dectype()=="void "||$<symbolinfo>3->get_dectype()=="void "){
														error_count++;
														fprintf(error,"Error at Line No.%d:  Type Mismatch \n\n",line_count);
														$<symbolinfo>$->set_dectype("int "); 
													}
										 			$<symbolinfo>$->set_dectype("int "); 
													
													$<symbolinfo>$->set_name($<symbolinfo>1->get_name()+$<symbolinfo>2->get_name()+$<symbolinfo>3->get_name());  

													}
		;

simple_expression : term {$<symbolinfo>$=new SymbolInfo();fprintf(parsertext,"Line at %d : simple_expression->term\n\n",line_count);
							fprintf(parsertext,"%s\n\n",$<symbolinfo>1->get_name().c_str());
							$<symbolinfo>$->set_dectype($<symbolinfo>1->get_dectype());
							$<symbolinfo>$->set_name($<symbolinfo>1->get_name());  
							 

							}
		  | simple_expression ADDOP term {$<symbolinfo>$=new SymbolInfo(); 
		  								fprintf(parsertext,"Line at %d : simple_expression->simple_expression ADDOP term\n\n",line_count);
		  								fprintf(parsertext,"%s%s%s\n\n",$<symbolinfo>1->get_name().c_str(),$<symbolinfo>2->get_name().c_str(),$<symbolinfo>3->get_name().c_str());
										//cout<<$<symbolinfo>3->get_dectype()<<endl;
										if($<symbolinfo>1->get_dectype()=="void "||$<symbolinfo>3->get_dectype()=="void "){
												error_count++;
												fprintf(error,"Error at Line No.%d:  Type Mismatch \n\n",line_count);
												$<symbolinfo>$->set_dectype("int "); 
										}else if($<symbolinfo>1->get_dectype()=="float " ||$<symbolinfo>3->get_dectype()=="float ")
											$<symbolinfo>$->set_dectype("float ");
										else  $<symbolinfo>$->set_dectype("int ");
										 	$<symbolinfo>$->set_name($<symbolinfo>1->get_name()+$<symbolinfo>2->get_name()+$<symbolinfo>3->get_name());  
										  }
		  ;

term :	unary_expression  {$<symbolinfo>$=new SymbolInfo();fprintf(parsertext,"Line at %d : term->unary_expression\n\n",line_count);
							fprintf(parsertext,"%s\n\n",$<symbolinfo>1->get_name().c_str()); 
							$<symbolinfo>$->set_dectype($<symbolinfo>1->get_dectype()); 
							
							$<symbolinfo>$->set_name($<symbolinfo>1->get_name()); 
							
							}
     |  term MULOP unary_expression {$<symbolinfo>$=new SymbolInfo();fprintf(parsertext,"Line at %d : term->term MULOP unary_expression\n\n",line_count);
	 								fprintf(parsertext,"%s%s%s\n\n",$<symbolinfo>1->get_name().c_str(),$<symbolinfo>2->get_name().c_str(),$<symbolinfo>3->get_name().c_str());
									 if($<symbolinfo>1->get_dectype()=="void "||$<symbolinfo>3->get_dectype()=="void "){
											error_count++;
											fprintf(error,"Error at Line No.%d:  Type Mismatch \n\n",line_count);
											$<symbolinfo>$->set_dectype("int "); 
									}else if($<symbolinfo>2->get_name()=="%"){
										 if($<symbolinfo>1->get_dectype()!="int " ||$<symbolinfo>3->get_dectype()!="int "){
											 error_count++;
											fprintf(error,"Error at Line No.%d:  Integer operand on modulus operator  \n\n",line_count);

										 } 
										 $<symbolinfo>$->set_dectype("int "); 
										
									 }
									else if($<symbolinfo>2->get_name()=="/"){
 									if($<symbolinfo>1->get_dectype()=="void "||$<symbolinfo>3->get_dectype()=="void "){
											error_count++;
											fprintf(error,"Error at Line No.%d:  Type Mismatch \n\n",line_count);
											$<symbolinfo>$->set_dectype("int "); 
									}
										else  if($<symbolinfo>1->get_dectype()=="int " && $<symbolinfo>3->get_dectype()=="int ")
										 $<symbolinfo>$->set_dectype("int "); 
										 else $<symbolinfo>$->set_dectype("float "); 
										
									 }
									 else{
										  if($<symbolinfo>1->get_dectype()=="void "||$<symbolinfo>3->get_dectype()=="void "){
											error_count++;
											fprintf(error,"Error at Line No.%d:  Type Mismatch \n\n",line_count);
											$<symbolinfo>$->set_dectype("int "); 
									}
										else  if($<symbolinfo>1->get_dectype()=="float " || $<symbolinfo>3->get_dectype()=="float ")
										 $<symbolinfo>$->set_dectype("float "); 
										 else $<symbolinfo>$->set_dectype("int "); 
									 }
									$<symbolinfo>$->set_name($<symbolinfo>1->get_name()+$<symbolinfo>2->get_name()+$<symbolinfo>3->get_name()); 
								
									 }
     ;

unary_expression : ADDOP unary_expression  {$<symbolinfo>$=new SymbolInfo(); fprintf(parsertext,"Line at %d : unary_expression->ADDOP unary_expression\n\n",line_count);
											fprintf(parsertext,"%s%s\n\n",$<symbolinfo>1->get_name().c_str(),$<symbolinfo>2->get_name().c_str());
											if($<symbolinfo>2->get_dectype()=="void "){
												error_count++;
												fprintf(error,"Error at Line No.%d:  Type Mismatch \n\n",line_count);
												$<symbolinfo>$->set_dectype("int "); 
											}else 
											 $<symbolinfo>$->set_dectype($<symbolinfo>2->get_dectype()); 	
											 $<symbolinfo>$->set_name($<symbolinfo>1->get_name()+$<symbolinfo>2->get_name()); 
										
										}
		 | NOT unary_expression {$<symbolinfo>$=new SymbolInfo();fprintf(parsertext,"Line at %d : unary_expression->NOT unary_expression\n\n",line_count);
				fprintf(parsertext,"!%s\n\n",$<symbolinfo>2->get_name().c_str()); 
				if($<symbolinfo>2->get_dectype()=="void "){
					error_count++;
					fprintf(error,"Error at Line No.%d:  Type Mismatch \n\n",line_count);
					$<symbolinfo>$->set_dectype("int "); 
				}else 
				$<symbolinfo>$->set_dectype($<symbolinfo>2->get_dectype());  
		 		$<symbolinfo>$->set_name("!"+$<symbolinfo>2->get_name()); 
		 
		 }
		 | factor {$<symbolinfo>$=new SymbolInfo();fprintf(parsertext,"Line at %d : unary_expression->factor\n\n",line_count);
		 		fprintf(parsertext,"%s\n\n",$<symbolinfo>1->get_name().c_str()); 
				// cout<<$<symbolinfo>1->get_dectype()<<endl;
				$<symbolinfo>$->set_dectype($<symbolinfo>1->get_dectype()); 
				$<symbolinfo>$->set_name($<symbolinfo>1->get_name()); 
				
		 }
		 ;
