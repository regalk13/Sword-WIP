with import <nixpkgs> {};
stdenv.mkDerivation {
  name = "env";
  nativeBuildInputs = [ pkg-config clang ];
  buildInputs = [
    sword
  ];
}
