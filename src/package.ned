package sr_aqn;

import ned.IdealChannel;


@license(LGPL);
//
// TODO documentation
//
network Network
{
    submodules:
        node: Node {
            @display("p=86,107");
        }
        node1: Node {
            @display("p=233,107");
        }
        cordinate: Cordinate {
            @display("p=156,162");
        }
    connections:
        cordinate.out1 --> IdealChannel --> node1.in_cor;
        cordinate.out0 --> IdealChannel --> node.in_cor;
        node.out --> IdealChannel --> node1.in;
        node1.out --> IdealChannel --> node.in;
}

