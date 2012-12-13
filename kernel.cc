Kernel::Kernel(double smoothlength)
  : h_(smoothinglength)
{}

Kernel::~Kernel()
{}

double Kernel::W(double r){
  return 0;
}

kVector Kernel::gradW(Kvector vec1, Kvector vec2){
  Kvector K = {0.,0.};
  return K; 
}
