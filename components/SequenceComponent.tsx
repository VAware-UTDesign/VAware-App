import { FontAwesome } from "@expo/vector-icons";
import React from "react";
import {View, Text, Pressable, StyleSheet, Animated} from 'react-native'
import { useNavigation } from "@react-navigation/core";

export default function Scenarios() {

    const navigation = useNavigation();

    return(        
        <Pressable 
            style={styles.eventContainer}
            onPress = {() => navigation.navigate('Sequences')}
        >
            <Text style={styles.cuffName}>RUA</Text>
            <View style={styles.volumeContainer}>
                <FontAwesome name='volume-up' size={40} color="white"/>
            </View>
            <View style={styles.example}>
            </View>
        </Pressable>
    )
}

const styles = StyleSheet.create({
    eventContainer: {
        flexDirection: 'row',
        margin: 10,
        height: 80,
        width: 320,
        borderRadius: 15,
        backgroundColor: 'grey',
        justifyContent: 'flex-start',
        alignItems: 'center'
    },
    cuffName: {
        fontSize: 40,
        marginLeft: 30,
        color: 'white',
    },
    volumeContainer: {
        marginLeft: 140
    },
    absoluteFill: {

    },example: {
        marginVertical: 24,
        
    },
})

//waist
//RUA
//RW
//N
//LW
//LUA